#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ResourceManager.h"


class GameObject {
public:
	GameObject(const sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& size);
	virtual ~GameObject() = default;
	virtual void draw(sf::RenderWindow& window) ;
	sf::FloatRect getGlobalBounds() const;
	void gotEaten(bool toChange) { m_beenEaten = toChange; }
	bool beenEaten() const { return m_beenEaten; }
	void goToStart() { m_character.setPosition(m_initPos); }

private:
	bool m_beenEaten;
	sf::Vector2f m_initPos;
	
protected:
	sf::RectangleShape m_character;
};