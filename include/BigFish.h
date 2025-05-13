#pragma once
#include "OtherFish.h"
#include "ObjectFactory.h"
#include "ResourceManager.h"
#include <random>
#include <ctime>

class BigFish : public OtherFish {
public:
	BigFish(const sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& size, int frameCount, int frameRow);

private:
	static bool m_registerit;

};