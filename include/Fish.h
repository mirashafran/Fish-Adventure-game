#pragma once

#include "MovingObject.h"
#include "NormalFishState.h"
#include "ProtectedFishState.h"
#include "DeadFishState.h"

//#include "LoadException.h"

class Fish : public MovingObject {

public:
	Fish(const sf::Texture* texture, const sf::Vector2f& pos, const sf::Vector2f& size);
	virtual void move(float deltaTimet) override;
	void setTexture(const sf::Texture* texture) { m_character.setTexture(texture); }
	void needToDie(bool need) {m_die=need; }
	void addScore(int score) {m_score += score;	}
	int getScore() const { return m_score; }
	int getLife() const { return m_life; }
	void setLife(int life) { m_life += life; }
	void resetLife() { m_life = 3; }
	void setCollectedKeys(int keys) { m_collectedKeys += keys; }
	int getCollectedKeys() const { return m_collectedKeys; }
	bool gameOver() const { return m_gameOver; }
	void setGameOver(bool gameOver) { m_gameOver = gameOver; }
	bool win() const { return m_win; }
	void setWin(bool win) { m_win = win; }
	void setState(std::unique_ptr<FishState> newState);
	void update();
	void handleCollisions(GameObject& gameObject);

private:
	int m_score;
	int m_life;
	int m_collectedKeys;
	bool m_gameOver;
	bool m_win;
	std::unique_ptr<FishState> m_currentState;
	bool m_die;



};