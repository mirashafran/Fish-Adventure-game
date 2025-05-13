#pragma once
#include "Fish.h"
#include "StaticObject.h"
#include <vector>
#include <unordered_map>
#include <memory>
#include "ObjectFactory.h"
#include "Macros.h"
#include "OtherFish.h"

class collisions;

class Board {

public:
	Board() {}
	void spawn();
	void draw(sf::RenderWindow& window);
	void moveObjects(float deltaTime, const Fish& fish);
	void checkCollisions(Fish& fish);
	void update(float deltaTime);
	static void needToFreeze(bool freeze) { m_freeze = freeze; }
	void reset();

private:

	//----members----
	static bool m_freeze;
	sf::Clock m_freezeTimer;
	std::unordered_map<std::string, int> m_objectCounts;
	std::vector<std::unique_ptr<OtherFish>> m_movingObjects;
	std::vector<std::unique_ptr<StaticObject>> m_StaticObjects;

	//----functions----
	sf::FloatRect inflatedBounds(const sf::FloatRect& originalBounds, const sf::Vector2f& inflationFactor) const;
	sf::Vector2f getInflationFactor(const GameObject& obj) const;
	void movingWithFishAndStatic(Fish& fish);
	void checkMovingCount();
	void updateAfterCollision();
	void setObjectCount(const std::string& type);
	bool inBounds(sf::FloatRect rect) const;
	void addObject(const std::string& type, int requiredCount);
	sf::FloatRect getGlobalBounds() const;

};