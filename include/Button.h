#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Command.h"
#include "ResourceManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Macros.h"

class Button {
public:

    Button () {}
    Button(const sf::Text& text, std::unique_ptr<Command> command);
    Button(const sf::Texture& texture, std::unique_ptr<Command> command);
    Button (const sf::Texture& texture);
    void setPosition(const sf::Vector2f& position);
    void draw(sf::RenderWindow& window, const sf::Vector2f& mousePosition);
    bool isClicked(const sf::Vector2f& location) const;
    void execute() const;
    sf::String getString() const { return m_text.getString().toAnsiString(); }
    std::unique_ptr<Command> getCommand() { return std::move(m_command); }
    void setTexture(const sf::Texture* texture) { m_button.setTexture(texture); }


private:
    void updateHover(const sf::Vector2f& mousePosition);

    sf::Text m_text;
    sf::RectangleShape m_button;
    sf::Vector2f m_position;
    std::unique_ptr<Command> m_command;
};


class HomeButton :public Button
{
    public:
        HomeButton(const sf::Texture& texture): Button(texture) {}
};

class PauseButton :public Button
{
    public:
	    PauseButton(const sf::Texture& texture) : Button(texture) {}
};