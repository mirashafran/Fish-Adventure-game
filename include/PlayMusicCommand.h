#pragma once
#include "Command.h"
#include "ResourceManager.h"
#include <SFML/Audio.hpp>

class PlayMusicCommand : public Command
{
public:
    PlayMusicCommand(sf::RenderWindow& window) : Command(window) {}
    void execute() override
    {
        sf::Music& music = ResourceManager::getInstance().getMusic();
        if (music.getStatus() != sf::Music::Playing)
        {
            music.play();
        }
        else
        {
            music.pause();
        }
    }
};