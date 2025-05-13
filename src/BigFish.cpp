#include "BigFish.h"	


BigFish::BigFish(const sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& size, int frameCount, int frameRow)
    : OtherFish(texture, position, size, frameCount, frameRow)
{
    m_speed = BIG_FISH_SPEED;
}

// Register the object to the factory
bool BigFish::m_registerit = ObjectFactory<OtherFish>::getInstance().registerit("BigFish", []() -> std::unique_ptr<OtherFish> {

    // Generate random position
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> posX(500.0f, BOARD_WIDTH-100.0f); 
    std::uniform_real_distribution<float> posY(250.0f, BOARD_HEIGHT - 300.0f);  

    sf::Vector2f randomPosition(posX(gen), posY(gen));

    return std::make_unique<BigFish>(
        ResourceManager::getInstance().getTexture("movingSprite"), randomPosition, BIG_FISH_SIZE, 6, 2);
    });

