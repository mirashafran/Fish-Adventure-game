#include "OtherFish.h"

bool OtherFish::m_freeze = false;

OtherFish::OtherFish(const sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& size, int frameCount, int frameRow) :
	MovingObject(texture, position, size, frameCount, frameRow, 16, 24)
{}

//other fish movment
void OtherFish::move(float deltaTime)
{
	m_prevPos = m_character.getPosition();
	m_character.move(m_direction * m_speed * deltaTime);
	updateImage(m_direction);
	updatePhoto(deltaTime);

}

//set the direction of the fish,
void OtherFish::setDirection(const sf::Vector2f& fishPos, const sf::Vector2f& fishSize)
{
	float dist = distance(m_character.getPosition(), fishPos);

	if (m_freeze)
	{
		freeze();
		
	}

	// If the fish is close enough to the main fish, chase it
	else if (dist < MAX_DISTANCE)
	{
		if (m_character.getSize().x-50 > fishSize.x && m_character.getSize().y > fishSize.y)
			ChaseTheFish(fishPos);

		else
			EscapeFromTheFish(fishPos);
	}
	else
		randomDirection();
}

float OtherFish::distance(const sf::Vector2f& pos1, const sf::Vector2f& pos2)
{
	float dx = pos1.x - pos2.x;
	float dy = pos1.y - pos2.y;
	return std::sqrt(dx * dx + dy * dy);
}

//set the direction of the fish to random direction
void OtherFish::randomDirection()
{
	// Generate random number between 1 and 4
	int random = std::rand() % 4 + 1;

	// Set direction based on random number
	switch (random)
	{
	case 1:
		m_direction = RIGHT_DIRECTION;
		break;
	case 2:
		m_direction = LEFT_DIRECTION;
		break;
	case 3:
		m_direction = DOWN_DIRECTION;
		break;
	case 4:
		m_direction = UP_DIRECTION;
		break;
	default:
		break;
	}
}

//set the direction of the fish to chase the main fish
void OtherFish::ChaseTheFish(const sf::Vector2f& fishPos)
{
	// Set direction towards the main fish
	m_direction.x = fishPos.x - m_character.getPosition().x;
	m_direction.y = fishPos.y - m_character.getPosition().y;

	// Normalize the direction vector
	float length = std::sqrt(m_direction.x * m_direction.x + m_direction.y * m_direction.y);

	if (length != 0)
	{
		m_direction.x /= length;
		m_direction.y /= length;
	}
}

//set the direction of the fish to escape from the main fish
void OtherFish::EscapeFromTheFish(const sf::Vector2f& fishPos)
{
	// Set direction towards the main fish
	m_direction.x = m_character.getPosition().x - fishPos.x;
	m_direction.y = m_character.getPosition().y - fishPos.y;

	// Normalize the direction vector
	float length = std::sqrt(m_direction.x * m_direction.x + m_direction.y * m_direction.y);

	if (length != 0)
	{
		m_direction.x /= length;
		m_direction.y /= length;
	}
}

//set the fish to freeze
void OtherFish::freeze()
{
	m_direction = FREEZE;
}