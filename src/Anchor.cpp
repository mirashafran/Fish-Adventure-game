#include "Anchor.h"



bool Anchor::m_registerit = ObjectFactory<StaticObject>::getInstance().registerit("Anchor", []() -> std::unique_ptr<StaticObject> {

    static int position = 0;
    std::vector<sf::Vector2f> positions = StaticObject::readPositionsFromFile("Anchor");

    position++;
    if (position >= positions.size())
        position = 0;

    return std::make_unique<Anchor>(ResourceManager::getInstance().getTexture("staticTexture"), positions[position], ANCHOR_SIZE, 9);

    });