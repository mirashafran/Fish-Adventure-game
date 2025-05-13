#include "SmallFish.h"	

SmallFish::SmallFish(const sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& size, int frameCount, int frameRow)
    : OtherFish(texture, position, size, frameCount, frameRow)
{
    m_speed = SMALL_FISH_SPEED;
}

bool SmallFish::m_registerit = ObjectFactory<OtherFish>::getInstance().registerit("SmallFish", []() -> std::unique_ptr<OtherFish> {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> posX(200.0f, BOARD_WIDTH - 100.0f);
    std::uniform_real_distribution<float> posY(250.0f, BOARD_HEIGHT - 300.0f);
 
    sf::Vector2f randomPosition(posX(gen), posY(gen));

    int randRow = rand() % 5 + 4;
    return std::make_unique<SmallFish>(
        ResourceManager::getInstance().getTexture("movingSprite"), randomPosition, SMALL_FISH_SIZE, 24, randRow);
    });



