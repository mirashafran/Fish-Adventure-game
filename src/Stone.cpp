#include "Stone.h"

bool Stone::m_registerit = ObjectFactory<StaticObject>::getInstance().registerit("Stone", []() -> std::unique_ptr<StaticObject> {

    static int position = 0;
    std::vector<sf::Vector2f> positions = StaticObject::readPositionsFromFile("Stone");

    position++;
    if (position >= positions.size())
        position = 0; 

    //random from row 3-5
    int random = rand() % 3 + 3;
    return std::make_unique<Stone>(
        ResourceManager::getInstance().getTexture("staticTexture"), positions[position], STONE_SIZE, random);

    });