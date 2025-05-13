#pragma once
#include "Fish.h"

class Bar {
public:
	Bar() : m_score(0) {}
	void printData(sf::RenderWindow& window, const std::unique_ptr<Fish>& fish);
	void printScoreForEnd(sf::RenderWindow& window);


private:
	sf::Text makeText(const std::string& str, const sf::Font* font);
	void printDataBar(sf::RenderWindow& window);
	int m_score;

};