#include "Key.h"

bool Key::m_registerit = ObjectFactory<StaticObject>::getInstance().registerit("Key", []() -> std::unique_ptr<StaticObject> {

    //read the positions from file
    static int position = 0;
    std::vector<sf::Vector2f> positions = StaticObject::readPositionsFromFile("Key");

    position++;
    if (position >= positions.size())
        position = 0; 

    return std::make_unique<Key>(
        ResourceManager::getInstance().getTexture("staticTexture"), positions[position], KEY_SIZE, 8);

    });