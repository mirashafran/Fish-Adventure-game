#include "CrazyFishState.h"
#include "Fish.h"


void CrazyFishState::update(Fish& fish)
{
    if (m_clock.getElapsedTime().asSeconds() > CRAZY_TIME)  // if the time of the crazy state is over, set the fish to normal state
    {
        fish.setState(std::make_unique<NormalFishState>());
        fish.setSize (NORMAL_FISH_SIZE);
    }
}

void CrazyFishState::onEnter(Fish& fish)  // set the fish to crazy state
{
    m_fishSize = fish.getSize();
    m_clock.restart();
    fish.setTexture(ResourceManager::getInstance().getTexture("crazyTexture"));
    fish.setSize(CRAZY_FISH_SIZE);
    fish.setSpeed(CRAZY_SPEED);
}

void CrazyFishState::onExit(Fish& fish)  // set the fish to normal state
{
	fish.setSize(m_fishSize);
	fish.setSpeed(MOVEMENT_SPEED);

}

//Protected state collision logic
void CrazyFishState::handleCollision(Fish& fish, GameObject& other)
{
    if ( typeid(other) == typeid(Shark)|| typeid(other) == typeid(BigFish) || typeid(other) == typeid(MediumFish))
    {
        ResourceManager::getInstance().getSound(EAT_SOUND);
        other.gotEaten(true);

    }
    if (typeid(other) == typeid(Shark))
	{
		fish.addScore(30);
	}
}