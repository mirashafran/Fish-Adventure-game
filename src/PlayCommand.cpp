
#include "PlayCommand.h"

PlayCommand::PlayCommand(sf::RenderWindow& window) : Command(window), isPaused(false)
{
    m_fish = std::make_unique<Fish>(ResourceManager::getInstance().getTexture("fishTexture"), FISH_START_POS, FISH_INIT_SIZE);
	m_hook = std::make_unique<FishHook>(ResourceManager::getInstance().getTexture("fishingHookTexture"), HOOK_START_POS, HOOK_SIZE);
	makeGameButtons();
}

void PlayCommand::makeGameButtons()  //create the buttons of the game
{
	m_homeButton = std::make_unique<HomeButton>(*(ResourceManager::getInstance().getTexture("returnButton")));
	m_pauseButton = std::make_unique<PauseButton>(*(ResourceManager::getInstance().getTexture("pauseButton")));
	m_musicButton = std::make_unique<Button>(*(ResourceManager::getInstance().getTexture("musicButton")), std::make_unique<PlayMusicCommand>(m_window));

	m_homeButton->setPosition(HOME_BUTTON_P);
	m_pauseButton->setPosition(PAUSE_BUTTON_P);
	m_musicButton->setPosition(MUSIC_BUTTON_P);
	
}

void PlayCommand:: execute()
{
	ResourceManager::getInstance().playMusic("waveSound.wav");
		
	sf::Clock clock;

	m_fish->startMoving(sf::Vector2f(FISH_START_POS.x, FISH_START_POS.y - 500), FISH_START_POS, MOVE_DURATION, false);

	while (m_window.isOpen())
	{	
		m_board.spawn();  //spawn the objects on the board
		
		const auto deltaTime = clock.restart();
	
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (handleMouseEvents())  //check if the buttons and handle click on them
				{
					return;
				}
			}
		}

		if(!isPaused)  //if the game is not paused, continue the game
		{
			if (updateGame(deltaTime.asSeconds()))
			{
				return;
			}
		}

		handleView(); 
		draw();
	}	
}

bool PlayCommand::handleMouseEvents()
{
	sf::Vector2f mousePosition = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

	if (m_homeButton->isClicked(mousePosition))  //if the home button is clicked, go back to the main menu and reset the game
	{
		resetGame();
		m_fish->setState(std::make_unique<NormalFishState>());  
		return true;
	}

	if (m_pauseButton->isClicked(mousePosition))
	{
		isPaused = !isPaused;
	}

	if (m_musicButton->isClicked(mousePosition))
	{
		m_musicButton->execute();
	}
	return false;
}

bool PlayCommand::updateGame(float deltaTime)  //update the game
{
	if (m_fish->isFalling()) //    // If the fish is currently falling, update its movement
	{
		m_fish->updateMoving(deltaTime);
	}

	else  //start the game normally
	{
		m_fish->update();
	
		if (checkGameOver() || checkWin())
		{
			return true;
		}

		m_fish->move(deltaTime);
		m_board.moveObjects(deltaTime, *m_fish);
		m_board.checkCollisions(*m_fish);
		hookCollision();
	}

	// Handle hook movement
	m_hook->move(deltaTime);

	return false;
}

bool PlayCommand::checkGameOver()
{
	if (m_fish->gameOver() || m_fish->getLife() <= 0)
	{
		ResourceManager::getInstance().getSound(GAME_OVER_SOUND);
		displayEndScreen("gameOver");
		resetGame();

		return true;
	}
	return false;
}

bool PlayCommand::checkWin()
{
	if (m_fish->win())
	{
		ResourceManager::getInstance().getSound(WIN_SOUND);
		displayEndScreen("win");
		resetGame();
		return true;
	}
	return false;
}

void PlayCommand::displayEndScreen(const std::string& screen)
{
	sf::Clock timer;
	sf::Time elapsedTime = sf::Time::Zero;

	while (elapsedTime < sf::seconds(3))   //display end screen for 3 seconds
	{
		m_window.clear();
		elapsedTime += timer.restart();
		
		ResourceManager::getInstance().cover(m_window, screen);

		m_bar.printScoreForEnd(m_window);
		m_window.display();
	}
}

void PlayCommand::handleView()  //handle the view of the game according to the fish position 
{
	sf::Vector2f pos = START_POS;
	m_view.reset(sf::FloatRect(0,0, WINDOW_WIDTH, WINDOW_HEIGHT));
	m_view.setViewport(sf::FloatRect(0, 0, 1, 1));
	m_view.setCenter(m_fish->getPosition());

	pos.x = m_fish->getPosition().x + 10 - (WINDOW_WIDTH / 2);
	pos.y = m_fish->getPosition().y + 10 - (WINDOW_HEIGHT/2);

	if (pos.x < 0)
		pos.x = 0;
	else if (pos.x > BOARD_WIDTH - WINDOW_WIDTH)
		pos.x = BOARD_WIDTH - WINDOW_WIDTH;

	if (pos.y < 0)
		pos.y = 0;
	else if (pos.y > BOARD_HEIGHT - WINDOW_HEIGHT)
		pos.y = BOARD_HEIGHT - WINDOW_HEIGHT;

	m_view.reset(sf::FloatRect(pos.x, pos.y, WINDOW_WIDTH, WINDOW_HEIGHT));

}

void PlayCommand::draw()
{
	m_window.clear();

	// Draw game elements with the game view
	m_window.setView(m_view);
	ResourceManager::getInstance().cover(m_window, "gameBackground");

	m_fish->draw(m_window);
	m_board.draw(m_window);
	m_hook->draw(m_window);

	// Switch to default view for drawing UI elements
	m_window.setView(m_window.getDefaultView());
	m_homeButton->draw(m_window, sf::Vector2f(sf::Mouse::getPosition(m_window)));
	m_pauseButton->draw(m_window, sf::Vector2f(sf::Mouse::getPosition(m_window)));
	m_musicButton->draw(m_window, sf::Vector2f(sf::Mouse::getPosition(m_window)));

	m_bar.printData(m_window, m_fish);

	m_window.display();
}

void PlayCommand::resetGame()  //reset the game after game over or win
{
	m_fish->resetLife();	
	m_fish->addScore(-m_fish->getScore());
	m_fish->setSize(FISH_INIT_SIZE);
	m_board.reset();
	m_fish->setPosition(FISH_START_POS);
	m_fish->setGameOver(false);
	m_fish->setWin(false);
	m_fish->setCollectedKeys(-(m_fish->getCollectedKeys()));
	isPaused = false;
	m_hook->setPosition(HOOK_START_POS);
	m_hook->setHookFallCount(0);
	m_hook->setHookXOffset(HOOK_X_OFFSET);	
}

void PlayCommand::hookCollision()  //check if the hook collides with the fish
{
	if (m_fish->getGlobalBounds().intersects(m_hook->getGlobalBounds()))
	{		
		processCollision(*m_fish, *m_hook);
	}
}