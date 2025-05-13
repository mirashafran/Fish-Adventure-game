#include "GameObject.h"

GameObject::GameObject(const sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& size) : m_beenEaten(false), m_initPos(position)
{
	m_character.setTexture(texture);
	m_character.setPosition(position);
	m_character.setSize(size);
}

void GameObject::draw(sf::RenderWindow& window) 
{
	window.draw(m_character);
}

sf::FloatRect GameObject::getGlobalBounds() const
{
	return m_character.getGlobalBounds();
}