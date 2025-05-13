#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ResourceManager.h"
#include "Menu.h"
#include "PlayCommand.h"	

class Controller {

public:
	Controller();
	void run();

private:
	sf::RenderWindow m_window;
	Menu m_menu;

};
