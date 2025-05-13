#include "ProtectedFishState.h"
#include "Fish.h"

void ProtectedFishState::update(Fish& fish)
{
    if (m_protectionClock.getElapsedTime().asSeconds() > PROTECTION_DURATION)
    {
        fish.setState(std::make_unique<NormalFishState>());
    }
}

void ProtectedFishState::onEnter(Fish& fish)
{
    m_protectionClock.restart();
    fish.setTexture(ResourceManager::getInstance().getTexture("protectedTexture"));
}

void ProtectedFishState::onExit(Fish& )
{
    //intentionally left empty
}


void ProtectedFishState::handleCollision(Fish& fish, GameObject& other)
{

    if (typeid(other) == typeid(Stone))
    {
        fish.setPrevPosition();
	}
    if (typeid(other) == typeid(Anchor))
    {
        if (fish.getSize() == FISH_INIT_SIZE)
        {
            fish.setPrevPosition();

        }
        fish.setSize(FISH_INIT_SIZE);
    }

    if (typeid(other) == typeid(FishHook))
	{
		fish.setState(std::make_unique<NormalFishState>());
        fish.setPrevPosition();
	}

}