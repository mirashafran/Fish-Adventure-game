#pragma once
#include "OtherFish.h"
#include "ObjectFactory.h"
#include "ResourceManager.h"
#include <random>
#include <ctime>

class SmallFish : public OtherFish {
public:
	SmallFish(const sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& size, int frameCount, int frameRow);

private:
	static bool m_registerit;


};