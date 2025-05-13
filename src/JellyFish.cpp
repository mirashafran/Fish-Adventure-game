#include "JellyFish.h"	

bool JellyFish::m_registerit = ObjectFactory<OtherFish>::getInstance().registerit("JellyFish", []() -> std::unique_ptr<OtherFish> {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> posX(400.0f, BOARD_WIDTH-100.0f);
    std::uniform_real_distribution<float> posY(250.0f, BOARD_HEIGHT-300.0f);

    sf::Vector2f randomPosition(posX(gen), posY(gen));

    return std::make_unique<JellyFish>(
        ResourceManager::getInstance().getTexture("movingSprite"), randomPosition, JELLY_FISH_SIZE, 1, 15);
    });


JellyFish::JellyFish(const sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& size, int frameCount, int frameRow)
    : OtherFish(texture, position, size, frameCount, frameRow)
{
    m_speed = JELLY_FISH_SPEED;
}

// The jellyfish moves randomly
void JellyFish::move(float deltaTime)
{
    int horizontalDirection = (std::rand() % 2 == 0) ? -1 : 1; // Generates -1 or 1

    // Random vertical direction: either up (-1) or down (1)
    int verticalDirection = (std::rand() % 2 == 0) ? -1 : 1; // Generates -1 or 1

    // Set the direction vector
    m_direction = sf::Vector2f(static_cast<float>(horizontalDirection), static_cast<float>(verticalDirection));

    m_character.move(m_direction * m_speed * deltaTime);
}
