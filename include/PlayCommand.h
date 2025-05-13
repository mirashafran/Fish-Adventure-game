#pragma once	
#include "Command.h"	
#include <iostream>
#include "ResourceManager.h"
#include "Macros.h"
#include "ObjectFactory.h"
#include "Button.h"
#include "Board.h"
#include "PlayMusicCommand.h"
#include "FishHook.h"
#include "Collisions.h"
#include "Bar.h"

class PlayCommand : public Command {

	public:
		PlayCommand(sf::RenderWindow &window);
		virtual void execute() override;
		void draw();
		void displayEndScreen(const std::string& screen);

	private:
		//----members----
		std::unique_ptr<Fish> m_fish;
		sf::View m_view;
		Board m_board;
		Bar m_bar;
		std::unique_ptr<FishHook> m_hook;
		std::unique_ptr<HomeButton> m_homeButton;
		std::unique_ptr<PauseButton> m_pauseButton;
		std::unique_ptr<Button> m_musicButton;
		bool isPaused;

		//----functions----
		void resetGame();
		void hookCollision();
		void handleView();
		void makeGameButtons();
		bool handleMouseEvents();
		bool updateGame(float deltaTime);
		bool checkWin();
		bool checkGameOver();


};