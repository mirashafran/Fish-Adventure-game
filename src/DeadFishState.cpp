#include "DeadFishState.h"
#include "Fish.h"

void DeadFishState::update(Fish& fish)
{
    while (m_clock.getElapsedTime().asSeconds() < 1)
    {
        fish.setState(std::make_unique<NormalFishState>());
        fish.goToStart();
    } 
}

// set the fish to dead state
void DeadFishState::onEnter(Fish& fish)
{
    m_clock.restart();
    fish.needToDie(true);
    fish.setSpeed(0);
    fish.setTexture(ResourceManager::getInstance().getTexture("deadFishTexture"));

}

void DeadFishState::onExit(Fish& fish)
{
	fish.needToDie(false);
}

void DeadFishState::handleCollision(Fish&, GameObject&)
{
  // intentionally empty
}