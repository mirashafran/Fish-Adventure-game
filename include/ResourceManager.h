#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Macros.h"
#include "LoadException.h"
#include <unordered_map>

//a singltone class to load and save all textures and sounds

class ResourceManager {
public:
    static ResourceManager& getInstance();
    void load();
    void cover(sf::RenderWindow& window, const std::string& backName) const;
    sf::Font* getFont();
    sf::Texture* getTexture(const std::string& textureName);
    void playMusic(const std::string& filename);
    sf::Music& getMusic();
    void stopMusic();
    void startMusic();
    void fillSoundBufVector();
    sf::Sound* getSound(int soundIndex);

private:
    //----functions----
    ResourceManager();
    void loadTexture(const std::string & fileName, const std::string & filePath);
    sf::SoundBuffer* getSoundBuffer(int index);

    //----members----
    sf::Font m_font;
    sf::Music m_music;
    sf::Sound m_sound;
    std::vector<sf::SoundBuffer> m_soundBuffers;
    std::vector<std::string> m_soundNames;
    std::unordered_map<std::string, sf::Texture> m_textures;

};