#include "Controller.h"

Controller::Controller()
    : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Fish Adventure"), m_menu(m_window)
{
    // Set icon
    sf::Texture* iconTexture = ResourceManager::getInstance().getTexture("icon");
    sf::Image iconImage = iconTexture->copyToImage();

    m_window.setIcon(iconImage.getSize().x, iconImage.getSize().y, iconImage.getPixelsPtr());


}


void Controller::run()
{
    ResourceManager::getInstance().fillSoundBufVector();

    ResourceManager::getInstance().playMusic("music.wav");
  

    m_window.setFramerateLimit(60);
    

    while (m_window.isOpen())
    {
        sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window));

        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                m_menu.activate(mousePosition);
            }
        }

        m_window.clear();
        m_menu.draw(m_window, mousePosition);
        m_window.display();
    }
   
}

