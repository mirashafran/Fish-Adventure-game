#include "Shell.h"

bool Shell::m_registerit = ObjectFactory<StaticObject>::getInstance().registerit("Shell", []() -> std::unique_ptr<StaticObject> {

    static int position = 0;
    std::vector<sf::Vector2f> positions = StaticObject::readPositionsFromFile("Shell");
    
    position++;
    if (position >= positions.size())
        position = 0;  

    return std::make_unique<Shell>(
        ResourceManager::getInstance().getTexture("staticTexture"), positions[position], SHELL_SIZE, 11);

    });