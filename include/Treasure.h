#pragma once
#include "StaticObject.h"
#include "ObjectFactory.h"
#include "Macros.h"
#include <SFML/Graphics.hpp>

class Treasure : public StaticObject {
public:
	using StaticObject::StaticObject;
	void cantOpen();
	virtual void draw(sf::RenderWindow& window)  override;


private:
	static bool m_registerit;
	bool m_reached = false;
	mutable sf::Clock m_timer;
};