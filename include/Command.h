#pragma once
#include <SFML/Graphics.hpp>

class Command {
public:
    Command(sf::RenderWindow& window) : m_window(window) {}
    Command() = default; // Default constructor
    virtual ~Command() = default;
    virtual void execute() = 0;

protected:
	sf::RenderWindow& m_window;
};

