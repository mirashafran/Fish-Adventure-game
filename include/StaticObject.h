#pragma once
#include "GameObject.h"
#include <fstream>
#include <sstream> 
#include <string>

class StaticObject : public GameObject {
public:
	StaticObject(const sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& size, int row);
	static std::vector<sf::Vector2f> readPositionsFromFile(const std::string& objectType);
};