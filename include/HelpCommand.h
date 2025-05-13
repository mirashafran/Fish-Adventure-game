#pragma once
#include "Command.h"
#include "ResourceManager.h"

class HelpCommand : public Command
{
public:
	HelpCommand(sf::RenderWindow& window) : Command(window) {}
	void execute() override;
};