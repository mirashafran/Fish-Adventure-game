#include "ResourceManager.h"
#include <iostream>


ResourceManager::ResourceManager()
{
    load(); 
    m_soundNames = { "eat", "collect", "growth", "win", "gameOver", "smallSize"};
}



ResourceManager& ResourceManager::getInstance()
{
    static ResourceManager instance;
    return instance;
}

// Load all resources
void ResourceManager::load() {
    // Load menu resources

    loadTexture("menuBackground", "background.png");
    loadTexture("buttonTexture", "menuButton.png");
    loadTexture("returnButton", "returnButton.png");
    loadTexture("pauseButton", "pauseButton.png");
    loadTexture("musicButton", "musicButton.png");

    // Load game textures
    loadTexture("gameBackground", "gameBack.png");
    loadTexture("fishTexture", "spritesheet.png");
    loadTexture("staticTexture", "staticSprite.png");
    loadTexture("deadFishTexture", "deadFish.png");
    loadTexture("win", "youWin.png");
    loadTexture("gameOver", "gameOver.png");
    loadTexture("movingSprite", "allSprite.png");
    loadTexture("protectedTexture", "protectedSprite.png");
    loadTexture("crazyTexture", "crazySprite.png");
    loadTexture("fishingHookTexture", "fishingHook.png");
    loadTexture("helpScreen", "helpScreen.png");
    loadTexture("infoBubbleTexture", "informationBubble.png");
    //icon
    loadTexture("icon", "icon.png");
}

// Load texture
void ResourceManager::loadTexture(const std::string& textureName, const std::string& filePath)
{
    sf::Texture texture;
    if (!texture.loadFromFile(filePath))
    {
        throw LoadException("Failed to load texture: " + filePath);
    }

    m_textures[textureName] = texture;
}

sf::Texture* ResourceManager::getTexture(const std::string& textureName) // get texture by name
{
    return &m_textures.at(textureName);
}


void ResourceManager::cover(sf::RenderWindow& window, const std::string& backName) const   // draw background
{
    sf::Sprite background;
    auto it = m_textures.find(backName);
    if (it != m_textures.end())
    {
        background.setTexture(it->second);
        window.draw(background);
    }
    else {
		throw std::invalid_argument("Invalid texture name: " + backName);
	}
}


sf::Font* ResourceManager::getFont()
{
    if (!m_font.loadFromFile("Font.otf"))
    {
        throw LoadException("Failed to load font");
    }
    return &m_font;
}

void ResourceManager::playMusic(const std::string& filename)
{
    if (!m_music.openFromFile(filename))
    {
        std::cerr << "Failed to load music: " << filename << std::endl;
    }

    m_music.setVolume(VOLUME);
    m_music.setLoop(true);
    m_music.play();
}


sf::Music& ResourceManager:: getMusic()  
{ 
    return m_music;
}
void ResourceManager::stopMusic()
{
    m_music.pause();
}
void ResourceManager::startMusic()
{ 
   m_music.play();
}

void ResourceManager::fillSoundBufVector()
{
    m_soundBuffers.resize(m_soundNames.size());
    for (int i = 0; i < m_soundBuffers.size(); i++)
    {
        if (!m_soundBuffers[i].loadFromFile(m_soundNames[i] + ".wav"))
            std::cerr << "Failed to load sound: " << m_soundNames[i] << std::endl;
    }
}
sf::SoundBuffer* ResourceManager::getSoundBuffer(int index)
{
    if (index < 0 || index >= m_soundBuffers.size())
    {
        throw std::out_of_range("Invalid sound index");
    }

    return &m_soundBuffers[index];
}

sf::Sound* ResourceManager::getSound(int soundIndex)
{
    const sf::SoundBuffer* soundBuffer = getSoundBuffer(soundIndex);
    m_sound.setBuffer(*soundBuffer);
    m_sound.play();

    return &m_sound;  
}