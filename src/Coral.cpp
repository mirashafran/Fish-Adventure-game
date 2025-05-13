#include "Coral.h"

bool Coral::m_registerit = ObjectFactory<StaticObject>::getInstance().registerit("Coral", []() -> std::unique_ptr<StaticObject> {

    //read positions from file
    static int position = 0;
    std::vector<sf::Vector2f> positions = StaticObject::readPositionsFromFile("Coral");

    position++;
    if (position >= positions.size())
        position = 0; 

    int random = std::rand() % 2;
    return std::make_unique<Coral>(
		ResourceManager::getInstance().getTexture("staticTexture"), positions[position], CORAL_SIZE, random);

    });
