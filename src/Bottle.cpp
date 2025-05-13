#include "Bottle.h"



bool Bottle::m_registerit = ObjectFactory<StaticObject>::getInstance().registerit("Bottle", []() -> std::unique_ptr<StaticObject> {

    //read the positions from file
    static int position = 0;
    std::vector<sf::Vector2f> positions = StaticObject::readPositionsFromFile("Bottle");

    position++;
    if (position >= positions.size())
        position = 0;  //throw exception

    return std::make_unique<Bottle>(
        ResourceManager::getInstance().getTexture("staticTexture"), positions[position], BOTTLE_SIZE, 10);

    });