#pragma once
#include "MovingObject.h"
#include "ObjectFactory.h"


class FishHook : public MovingObject {
public:
	FishHook(const sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& size);
	virtual void move(float deltaTime) override;
	void setHookXOffset(float offset) { m_hookXOffset = offset; }
	void setHookFallCount(int count) { m_hookFallCount = count; }


private:
	
	enum HookState { Inactive, Falling, Ascending };
	static bool m_registerit;
	HookState m_hookState;
	sf::Clock m_hookClock;
	sf::Time m_hookDelay; // Delay between actions
	int m_hookFallCount;
	int m_maxHookFalls;
	float m_hookXOffset;

};