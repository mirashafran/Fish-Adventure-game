#include "Bar.h"

//This function is responsible for printing the data of the fish on the screen
void Bar:: printData(sf::RenderWindow& window, const std::unique_ptr<Fish>& fish)
{
    sf::Text text;
    sf::Font* font;

    font = ResourceManager::getInstance().getFont();

    printDataBar(window);

    m_score= fish->getScore();
    std::string str = std::to_string(m_score);
    text = makeText("Score: " + str, font);
    text.setPosition(SCORE_DATA_POS);

    window.draw(text);

    int life = fish->getLife();
    str = std::to_string(life);
    text = makeText("Life: " + str, font);
    text.setPosition(LIFE_DATA_POS);
    window.draw(text);

    int keys = fish->getCollectedKeys();
    str = std::to_string(keys);
    text = makeText("Keys: " + str, font);
    text.setPosition(KEYS_DATA_POS);
    window.draw(text);
}


void Bar::printDataBar(sf::RenderWindow& window)
{
    sf::RectangleShape dataBar(BAR_SIZE);
    dataBar.setTexture(ResourceManager::getInstance().getTexture("buttonTexture"));
    dataBar.setPosition(BAR_POSITION);

    window.draw(dataBar);
}

//This function is responsible for printing the score of the fish at the end of the game
void Bar::printScoreForEnd(sf::RenderWindow& window)
{
    sf::Text text;
    sf::Font* font;

    font = ResourceManager::getInstance().getFont();
    std::string str = std::to_string(m_score);
    text = makeText("YOURE SCORE: " + str, font);
    text.setPosition(WINDOW_WIDTH / 2 - 220, WINDOW_HEIGHT / 2 + 70);
    text.setFillColor(sf::Color(255, 165, 0)); // Orange color
    text.setStyle(sf::Text::Bold);
    text.setCharacterSize(100);
    window.draw(text);
  

}

//This function is responsible for creating a text object
sf::Text Bar::makeText(const std::string& str, const sf::Font* font)
{
    sf::Text text;
    text.setFont(*font);
    text.setString(str);
    text.setCharacterSize(TEXT_SIZE);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    return text;
}
