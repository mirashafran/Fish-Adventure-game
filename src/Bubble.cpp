#include "Bubble.h"



bool Bubble::m_registerit = ObjectFactory<StaticObject>::getInstance().registerit("Bubble", []() -> std::unique_ptr<StaticObject> {

    //read positions from file
    static int position = 0;
    std::vector<sf::Vector2f> positions = StaticObject::readPositionsFromFile("Bubble");

    position++;
    if (position >= positions.size())
    {
        position = 0;  
    }

    return std::make_unique<Bubble>(
        ResourceManager::getInstance().getTexture("staticTexture"), positions[position], BUBBLE_SIZE, 6);

    });