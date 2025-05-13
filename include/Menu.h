#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Button.h"
#include "PlayCommand.h"
#include "ExitCommand.h"
#include "PlayMusicCommand.h"
#include "HelpCommand.h"

class Menu {
public:
    Menu(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window, const sf::Vector2f& mousePosition);
    void activate(const sf::Vector2f& mousePosition);

private:
    //----functions----
    sf::Text makeButton(const std::string& str, const sf::Font* font);
    void makeMenuItems(const sf::Font* font);

    //----members----
    sf::RenderWindow& m_window;
    std::vector<std::unique_ptr<Button>> m_menu;
};
