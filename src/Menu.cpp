#include "Menu.h"

Menu::Menu(sf::RenderWindow& window) : m_window(window)
{
    sf::Font* font;

    font = ResourceManager::getInstance().getFont();

    makeMenuItems (font);
   
}

void Menu::makeMenuItems(const sf::Font* font)
{
    // create the buttons
    sf::Text text = makeButton("Play", font);
    m_menu.emplace_back(std::make_unique<Button>(text, std::make_unique<PlayCommand>(m_window)));

    text = makeButton("Help", font);
    m_menu.emplace_back(std::make_unique<Button>(text, std::make_unique<HelpCommand>(m_window)));


    text = makeButton("Exit", font);
    m_menu.emplace_back(std::make_unique<Button>(text, std::make_unique<ExitCommand>(m_window)));

    m_menu.emplace_back(std::make_unique<Button>(*(ResourceManager::getInstance().getTexture("musicButton")), std::make_unique<PlayMusicCommand>(m_window)));

    for (int i = 0; i < m_menu.size() - 1; ++i)  // set the position of the buttons
    {
        m_menu[i]->setPosition(sf::Vector2f(MENU_POS_X, MENU_POS_Y + i * 100.0f));   // set the position of the buttons
    }

    m_menu[m_menu.size() - 1]->setTexture(ResourceManager::getInstance().getTexture("musicButton"));
    m_menu[m_menu.size() - 1]->setPosition(MUSIC_BUTTON_POS);
}

sf::Text Menu::makeButton(const std::string& str, const sf::Font* font)
{
    sf::Text text;
    text.setFont(*font);
    text.setString(str);
    text.setCharacterSize(TEXT_SIZE);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    return text;
}

void Menu::draw(sf::RenderWindow& window, const sf::Vector2f& mousePosition)
{
    window.clear();
    ResourceManager::getInstance().cover(window, "menuBackground");

    for (const auto& button : m_menu)
    {
        button->draw(window, mousePosition);
    }
}

void Menu::activate(const sf::Vector2f& mousePosition)  // check if the button is clicked and execute the command
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        for (const auto& button : m_menu)
        {
            if (button->isClicked(mousePosition)) 
            {
                button->execute();
            }
        }
    }
}