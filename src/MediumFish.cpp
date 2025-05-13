#include "MediumFish.h"	

MediumFish::MediumFish(const sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& size, int frameCount, int frameRow)
    : OtherFish(texture, position, size, frameCount, frameRow)
{
    m_speed = MEDIUM_FISH_SPEED;
}

bool MediumFish::m_registerit = ObjectFactory<OtherFish>::getInstance().registerit("MediumFish", []() -> std::unique_ptr<OtherFish> {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> posX(500.0f, BOARD_WIDTH-100.0f);
    std::uniform_real_distribution<float> posY(250.0f, BOARD_HEIGHT - 300.0f);

    sf::Vector2f randomPosition(posX(gen), posY(gen));

    return std::make_unique<MediumFish>(
        ResourceManager::getInstance().getTexture("movingSprite"), randomPosition, MEDIUM_FISH_SIZE, 6, 0);
    });

 