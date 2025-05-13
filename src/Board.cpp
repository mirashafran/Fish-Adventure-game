#include "Board.h"
#include "Collisions.h"

 bool Board:: m_freeze = false;

void Board::spawn()  //add objects to board
{	
	addObject("BigFish", REQUIRED_BIG_FISH);
	addObject("MediumFish", REQUIRED_MEDIUM_FISH);
	addObject("SmallFish", REQUIRED_SMALL_FISH);
	addObject("Shark", REQUIRED_SHARKS);
	addObject("Coral", REQUIRED_CORALS);
	addObject("Stone", REQUIRED_STONES);
	addObject("Key", REQUIRED_KEYS);
	addObject("Anchor", REQUIRED_ANCHOR);
	addObject("JellyFish", REQUIRED_JELLY_FISH);
	addObject("Treasure", REQUIRED_TREASURE);
	addObject("Bottle", REQUIRED_BOTTLES);
	addObject("Bubble", REQUIRED_BUBBLES);
	addObject("Shell", REQUIRED_SHELL);
}

// Spawns objects of the given type. Static objects are created once until the required count is reached,
// but won't respawn if removed. Moving objects are continually respawned to maintain the required count.

void Board::addObject(const std::string& type, int requiredCount) 
{
	if (m_objectCounts["class "+type] < requiredCount) //check if object count is less than required
	{
		if (auto p = ObjectFactory<OtherFish>::getInstance().create(type))  //create object using factory
		{
			m_movingObjects.emplace_back(std::move(p));
			m_objectCounts["class " + type]++;
		}
		
		else if (auto s = ObjectFactory<StaticObject>::getInstance().create(type)) //create object using factory
		{
			m_StaticObjects.emplace_back(std::move(s));
			m_objectCounts["class " + type]++;
		}
		else
		{
			throw std::runtime_error("Unknown object type: " + type);  //throw exception if there is no such object
		}
	}
}

void Board::setObjectCount (const std::string& type)  //decrease object count for the moving objects
{
	m_objectCounts[type]--;
}

void Board::update(float deltaTime) // update moving objects photo
{
	for (auto& obj : m_movingObjects)
	{
		obj->updatePhoto(deltaTime);
	}
}

void Board::draw(sf::RenderWindow& window)
{
	for (auto& obj : m_movingObjects)
	{
		obj->draw(window);
	}
	for (auto& obj : m_StaticObjects)
	{
		obj->draw(window);
	}
}

void Board::moveObjects(float deltaTime, const Fish& fish) 
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	sf::Vector2f fishPos = fish.getPosition();
	sf::Vector2f fishSize = fish.getSize();

	for (auto& obj : m_movingObjects)
	{
		obj->setDirection(fishPos, fishSize);
		obj->move(deltaTime);
	}
}

void Board::checkCollisions(Fish& fish)
{
	if (!inBounds(fish.getGlobalBounds())) // Handle fish and board collision
		fishWithBoard(fish, *this);

	movingWithFishAndStatic(fish);	

	// Check fish collision with static objects
	for (auto& obj : m_StaticObjects)
	{
		if (inflatedBounds(fish.getGlobalBounds(), getInflationFactor(fish)).intersects(inflatedBounds(obj->getGlobalBounds(), getInflationFactor(*obj))))
		{
			processCollision(fish, *obj);
		}
	}

	checkMovingCount();
	updateAfterCollision();
}

void Board::updateAfterCollision()  
{
	if (m_freezeTimer.getElapsedTime().asSeconds() > 5)  //if freeze timer is more than 5 seconds, unfreeze
	{
		OtherFish::needToFreeze(false);
	}

	m_StaticObjects.erase(std::remove_if(m_StaticObjects.begin(), m_StaticObjects.end(),    //erase object that has been eaten
		[](const auto& obj) { return obj->beenEaten(); }), m_StaticObjects.end());

	m_movingObjects.erase(std::remove_if(m_movingObjects.begin(), m_movingObjects.end(),    //erase object that has been eaten
		[](const auto& obj) { return obj->beenEaten(); }), m_movingObjects.end());

}

void Board::checkMovingCount()  //check if moving objects have been eaten
{
	for (auto& obj : m_movingObjects)
	{
		if (obj->beenEaten())
		{
			setObjectCount(typeid(*obj).name());
		}
	}
}

void Board::movingWithFishAndStatic(Fish& fish)
{
	for (auto& obj : m_movingObjects)
	{
		// Check moving objects collision with moving objects
		for (auto& obj2 : m_movingObjects)
		{
			if (obj != obj2 && inflatedBounds(obj->getGlobalBounds(), getInflationFactor(*obj)).intersects(inflatedBounds(obj2->getGlobalBounds(), getInflationFactor(*obj2))))
			{
				processCollision(*obj, *obj2);
			}
		}

		// Check moving objects collision with static objects
		for (auto& obj2 : m_StaticObjects)
		{
			if (obj->getGlobalBounds().intersects(obj2->getGlobalBounds()))
			{
				processCollision(*obj, *obj2);
			}
		}

		// Check moving objects collision with fish
		if (inflatedBounds(fish.getGlobalBounds(), getInflationFactor(fish)).intersects(inflatedBounds(obj->getGlobalBounds(), getInflationFactor(*obj))))
		{
			processCollision(fish, *obj);

			if (OtherFish::isFrozen())   //if need to freeze , reset clock
			{
				m_freezeTimer.restart();
			}
		}
	}
}


sf::FloatRect Board::inflatedBounds(const sf::FloatRect& originalBounds, const sf::Vector2f& inflationFactor) const  //inflate the bounds of the object
{
	return sf::FloatRect(
		originalBounds.left - inflationFactor.x,
		originalBounds.top - inflationFactor.y,
		originalBounds.width + 2 * inflationFactor.x,
		originalBounds.height + 2 * inflationFactor.y
	);
}

sf::Vector2f Board::getInflationFactor(const GameObject& obj) const  //get inflation factor for the object
{
	if (typeid(obj) == typeid(Fish))
		return sf::Vector2f(-25.f, -25.f);

	else if (typeid(obj) == typeid(Shark))
		return sf::Vector2f(-100.f, -100.f);

	else if (typeid(obj) == typeid(Anchor))
		return sf::Vector2f(-50.f, -50.f);
	
	else
		return sf::Vector2f(-20.f, -20.f); // Default inflation factor
}



sf::FloatRect Board::getGlobalBounds() const
{
	const float margin = 20.0f; //to increase the bounds
	return sf::FloatRect(START_POINT.x - margin, START_POINT.y - margin, BOARD_WIDTH + 2* margin, BOARD_HEIGHT + 2 * margin);
}


bool Board::inBounds(sf::FloatRect rect) const  //check if object is in board bounds
{
	auto bounds = this->getGlobalBounds();
	bool topLeft = bounds.contains(rect.left, rect.top);
	bool bottomLeft = bounds.contains(rect.left, rect.top + rect.height);
	bool topRight = bounds.contains(rect.left + rect.width, rect.top);
	bool bottomRight = bounds.contains(rect.left + rect.width, rect.top + rect.height);

	return (topLeft && topRight && bottomLeft && bottomRight);
}

void Board::reset()  //reset the board
{
	m_movingObjects.clear();
	m_StaticObjects.clear();
	m_objectCounts.clear();
}