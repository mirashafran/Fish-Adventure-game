#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ResourceManager.h"
#include "GameObject.h"
#include <cmath>


class MovingObject: public GameObject {

public:
		
	MovingObject(const sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& size, int frameCount, int frameRow, int rowsNum, int maxPhotos);
	~MovingObject() {}
	virtual void move(float deltaTime) = 0; 
	virtual void updatePhoto(float dt);
	sf::Vector2f getPosition() const { return m_character.getPosition(); }
	void setPosition(const sf::Vector2f& position) { m_character.setPosition(position); }
	sf::Vector2f getSize() const { return m_character.getSize(); }
	sf::Vector2f getDirection() const { return m_direction; }
	void setSize(const sf::Vector2f& size) { m_character.setSize(size); }
	void setPrevPosition();
	sf::Vector2f getPrevPosition() const { return m_prevPos; }
	void goToStart() { m_character.setPosition(m_initPos); }
	void updateImage(const sf::Vector2f& offset);
	void startMoving(const sf::Vector2f& startPos, const sf::Vector2f& endPos, float duration, bool ascending);
	void updateMoving(float deltaTime);
	bool isFalling() const { return m_isFalling; }
	bool isAscending() const { return m_isAscending; }
	void setSpeed(float speed) { m_speed = speed; }


protected:
		
	float m_speed;	
	sf::Vector2f m_direction;
	sf::Vector2f m_prevPos;
	bool m_isFalling;

private:
	//---functions---
	void setFrames(const sf::Texture* texture, int frameRow, int rowsNum, int maxPhotos);

	//---members---
	std::vector<sf::IntRect> m_frames;
	sf::Vector2f m_initPos;
	int m_frameCount;
	float m_frameDuration;
	int m_currentFrame;
	float m_elapsedTime;
	bool m_isAscending;
	sf::Vector2f m_moveStartPos;
	sf::Vector2f m_moveEndPos;
	float m_moveDuration;
	float m_moveElapsed;
};