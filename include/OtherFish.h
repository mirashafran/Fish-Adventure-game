#pragma once
#include "MovingObject.h"

class OtherFish : public MovingObject
{
	public:
		OtherFish(const sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& size, int frameCount, int frameRow);
		virtual void move(float deltaTime) override;
		void setDirection(const sf::Vector2f& fishPos, const sf::Vector2f& fishSize);
		void randomDirection();
		static bool isFrozen() { return m_freeze; }
		static void needToFreeze(bool freeze) { m_freeze = freeze; }


	private:
		//---functions---
		float distance(const sf::Vector2f& pos1, const sf::Vector2f& pos2);
		void ChaseTheFish(const sf::Vector2f& fishPos);
		void EscapeFromTheFish(const sf::Vector2f& fishPos);
		void freeze();

		//---members---
		static bool m_freeze;


};