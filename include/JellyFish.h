#pragma once

#include "OtherFish.h"
#include "ObjectFactory.h"
#include "ResourceManager.h"
#include <random>
#include <ctime>

class JellyFish : public OtherFish {

public:
	JellyFish(const sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& size, int frameCount, int frameRow);
	virtual void move(float deltaTime) override;

private:
	static bool m_registerit;

};