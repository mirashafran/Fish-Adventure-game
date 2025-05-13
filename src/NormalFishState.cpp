#include "NormalFishState.h"
#include "Fish.h"

void NormalFishState::update(Fish& ) 
{
    // intentionally empty
}

void NormalFishState::onEnter(Fish& fish)
{
    fish.setTexture(ResourceManager::getInstance().getTexture("fishTexture"));
}

void NormalFishState::onExit(Fish&)
{
	// intentionally empty
}


void NormalFishState::handleCollision(Fish& fish, GameObject& other)  // handle collision between normal fish and other game objects
{
    if (typeid(other) == typeid(Shark))
    {
        fish.setState(std::make_unique<DeadFishState>());

        fish.setLife(-1);
      
        ResourceManager::getInstance().getSound(EAT_SOUND);


	}
    else if (typeid(other) == typeid(BigFish) || typeid(other) == typeid(MediumFish))
    {
        fish.goToStart();
        fish.setLife(-1);
        other.goToStart();
        ResourceManager::getInstance().getSound(EAT_SOUND);

	}
    else if (typeid(other) == typeid(Stone))
    {
        fish.setPrevPosition();
    }
    else if (typeid(other) == typeid(Anchor))
    {
        if (fish.getSize() == FISH_INIT_SIZE)
        {
            fish.setPrevPosition();

        }
        fish.setSize(FISH_INIT_SIZE);
    }

    else if (typeid(other) == typeid(FishHook))
	{
		fish.setGameOver(true);
	}
}