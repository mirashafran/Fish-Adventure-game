#pragma once
#include "Command.h"

class ExitCommand : public Command
{
public:
	ExitCommand(sf::RenderWindow& window) : Command(window) {}
	void execute() override;

};