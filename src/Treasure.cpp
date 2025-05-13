#include "Treasure.h"

bool Treasure::m_registerit = ObjectFactory<StaticObject>::getInstance().registerit("Treasure", []() -> std::unique_ptr<StaticObject> {
    return std::make_unique<Treasure>(ResourceManager::getInstance().getTexture("staticTexture"), TREASURE_POSITION, TREASURE_SIZE, 7);

    });

void Treasure:: cantOpen()
{
    m_reached = true;
    m_timer.restart();
}

//draw the treasure, if the player reached the treasure, draw the info bubble
void Treasure::draw(sf::RenderWindow& window) 
{

	window.draw(m_character);

    if (m_reached)
    {
        if (m_timer.getElapsedTime().asSeconds() < 3)
        {
            sf::Sprite sprite(*(ResourceManager::getInstance().getTexture("infoBubbleTexture")));
            sprite.setPosition(TREASURE_POSITION.x - 120, TREASURE_POSITION.y - 180);
            sprite.setScale(0.2f, 0.2f);

            window.draw(sprite);
        }
        else
        {
            m_reached = false; // Reset the flag after 3 seconds
        }
    }
}
