#include "Fish.h"

Fish::Fish(const sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& size) 
    : MovingObject(texture, position, size, 6, 0, 1, 6), m_die(false),
     m_score(INIT_SCORE), m_life(FISH_LIFE), m_gameOver(false), m_collectedKeys(INIT_KEYS),
    m_win(false), m_currentState(std::make_unique<NormalFishState>())
{
    m_currentState->onEnter(*this);  // Initialize the state to Normal State
    m_speed = MOVEMENT_SPEED;
}

void Fish::update()
{
    m_currentState->update(*this);
}


void Fish::setState(std::unique_ptr<FishState> newState)  // Change the state of the fish if needed
{
    m_currentState->onExit(*this);
    m_currentState = std::move(newState);
    m_currentState->onEnter(*this);
}

void Fish::handleCollisions(GameObject& gameObject)
{
	m_currentState->handleCollision(*this, gameObject);
}

//the fish moves according to the key pressed
void Fish::move(float deltaTime)
{
    if (!isFalling())   // If the fish is not falling, it can move
    {
        m_direction = INIT_DIRECTION;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            m_direction.x += 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            m_direction.x -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            m_direction.y -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            m_direction.y += 1.0f;
        }
        if (m_die)
        {
			m_direction = sf::Vector2f(0.f, 0.f);
		}

        m_prevPos = m_character.getPosition();
        updateImage(m_direction);
        m_character.move(m_direction * deltaTime * m_speed);
        updatePhoto(deltaTime);
    }
}
