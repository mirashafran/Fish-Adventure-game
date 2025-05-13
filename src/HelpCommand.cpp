#include "HelpCommand.h"

//display the help screen
void HelpCommand::execute()
{
	sf::RenderWindow helpWindow(sf::VideoMode(HELP_WIDTH, HELP_HEIGHT), "Help Screen");

	while(helpWindow.isOpen())
	{
		ResourceManager::getInstance().cover(helpWindow, "helpScreen");

		helpWindow.display();

		sf::Event event;
		while (helpWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				helpWindow.close();
				break;
			}
		}
	}
}
	