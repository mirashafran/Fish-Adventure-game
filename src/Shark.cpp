#include "Shark.h"	

bool Shark::m_registerit = ObjectFactory<OtherFish>::getInstance().registerit("Shark", []() -> std::unique_ptr<OtherFish> {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> posX(400.0f, BOARD_WIDTH-100.0f);
    std::uniform_real_distribution<float> posY(250.0f, BOARD_HEIGHT - 300.0f);

    sf::Vector2f randomPosition(posX(gen), posY(gen));

	return std::make_unique<Shark>(
		ResourceManager::getInstance().getTexture("movingSprite"), randomPosition, SHARK_SIZE, 8, 13);
    });


Shark::Shark(const sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& size, int frameCount, int frameRow)
	: OtherFish(texture, position, size, frameCount, frameRow)
{
	m_speed = SHARK_SPEED;
}




