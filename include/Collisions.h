#pragma once
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include "GameObject.h"
#include "Fish.h"
#include "SmallFish.h"
#include "MediumFish.h"
#include "JellyFish.h"
#include "BigFish.h"
#include "Shark.h"
#include "Board.h"
#include "Coral.h"
#include "Stone.h"
#include "Anchor.h"
#include "PlayCommand.h"
#include "Key.h"
#include "Treasure.h"
#include "Bottle.h"
#include "Bubble.h"
#include "ProtectedFishState.h"
#include "CrazyFishState.h"
#include "FishHook.h"
#include "Shell.h"


//this namespace handles all collisions creating double v-table
namespace {


    void fishWithBoard(GameObject& fish, const Board& )
    {
        Fish& c_fish = dynamic_cast<Fish&>(fish);
        c_fish.setPrevPosition();
    }
    

    void FishWithSmallFish(GameObject& fish, GameObject& smallFish)
    {
		Fish& c_fish = dynamic_cast <Fish&> (fish);
		SmallFish& c_smallFish = dynamic_cast <SmallFish&> (smallFish);

        sf::Vector2f currentSize = c_fish.getSize();

        if (currentSize.x <= MAX_FISH_SIZE)
        {
            c_fish.setSize(sf::Vector2f(currentSize.x + SMALL_RESIZE, currentSize.y + SMALL_RESIZE));
        }


        ResourceManager::getInstance().getSound(GROWTH_SOUND);
        c_smallFish.gotEaten(true);
        c_fish.addScore(10);
	}


    //handle collision between fish and medium/big fish
    template<typename FishType>
    void FishWithOtherFish(GameObject& fish, GameObject& otherFish)
    {
        Fish& c_fish = dynamic_cast<Fish&>(fish);
        FishType& c_otherFish = dynamic_cast<FishType&>(otherFish);

        sf::Vector2f currentSize = c_fish.getSize();

        if (currentSize.x+50 > c_otherFish.getSize().x)
        {
            if (currentSize.x <= MAX_FISH_SIZE) {
                c_fish.setSize(sf::Vector2f(currentSize.x + BIG_RESIZE, currentSize.y + BIG_RESIZE));
            }
            c_fish.addScore(20);
            ResourceManager::getInstance().getSound(GROWTH_SOUND);
            c_otherFish.gotEaten(true);

        }
        else
        {
            c_fish.handleCollisions(c_otherFish);
        }
    }


    template<typename FishType>
    void OtherFishWithOtherFish(GameObject& otherFish1, GameObject& otherFish2)
    {
        FishType& c_otherFish1 = dynamic_cast<FishType&>(otherFish1);
		FishType& c_otherFish2 = dynamic_cast<FishType&>(otherFish2);

		c_otherFish1.randomDirection();
		c_otherFish2.randomDirection();
	}



    void FishWithShark(GameObject& fish, GameObject& shark)
    {
		Fish& c_fish = dynamic_cast <Fish&> (fish);
		Shark& c_shark = dynamic_cast <Shark&> (shark);

        c_fish.handleCollisions(c_shark);        
	}

    void FishWithJellyFish(GameObject& , GameObject& jellyFish)
    {
		JellyFish& c_jellyFish = dynamic_cast <JellyFish&> (jellyFish);

        OtherFish::needToFreeze(true);
        c_jellyFish.gotEaten(true);
	}


    void FishWithCoral(GameObject& fish, GameObject& coral)
    {
        Fish& c_fish = dynamic_cast <Fish&> (fish);
        Coral& c_coral = dynamic_cast <Coral&> (coral);

        ResourceManager::getInstance().getSound(COLLECT_SOUND);
        c_coral.gotEaten(true);
        c_fish.setState(std::make_unique<CrazyFishState>());
    }


    void FishWithStone(GameObject& fish, GameObject& stone)
	{
		Fish& c_fish = dynamic_cast <Fish&> (fish);
		Stone& c_stone = dynamic_cast <Stone&> (stone);

        c_fish.handleCollisions(c_stone);		
	}


    template<typename FishType>
    void OtherFishWithStone(GameObject& otherFish, GameObject& )
    {
        FishType& c_otherFish = dynamic_cast <FishType&> (otherFish);

        c_otherFish.setPrevPosition();

    }


    void fishWithAnchor(GameObject& fish, GameObject& anchor)
	{
		Fish& c_fish = dynamic_cast <Fish&> (fish);
		Anchor& c_anchor = dynamic_cast <Anchor&> (anchor);

        c_fish.handleCollisions(c_anchor);
	}


    void FishWithKey(GameObject& fish, GameObject& key)
	{
		Fish& c_fish = dynamic_cast <Fish&> (fish);
		Key& c_key = dynamic_cast <Key&> (key);

        ResourceManager::getInstance().getSound(COLLECT_SOUND);
		c_key.gotEaten(true);
        c_fish.setCollectedKeys(1);
	}

    void FishWithTreasure(GameObject& fish, GameObject& treasure)
    {
        Fish& c_fish = dynamic_cast <Fish&> (fish);
        Treasure& c_treasure = dynamic_cast <Treasure&> (treasure);

        if(c_fish.getCollectedKeys() == REQUIRED_KEYS)
		{
			c_fish.setWin(true);
		}
		else
		{
			c_fish.setPrevPosition();
           
            c_treasure.cantOpen();
		}
    }

    void FishWithBottle(GameObject& fish, GameObject& bottle)
	{
		Fish& c_fish = dynamic_cast <Fish&> (fish);
		Bottle& c_bottle = dynamic_cast <Bottle&> (bottle);

		c_bottle.gotEaten(true);

        ResourceManager::getInstance().getSound(SMALL_SIZE_SOUND);

        sf::Vector2f currentSize = c_fish.getSize();
        
        if (currentSize.x > FISH_INIT_SIZE.x) 
        {
            c_fish.setSize(sf::Vector2f(currentSize.x - BIG_RESIZE, currentSize.y - BIG_RESIZE));
        }        
	}


    void fishWithBubble(GameObject& fish, GameObject& bubble)
    {
        Fish& c_fish = dynamic_cast <Fish&> (fish);
		Bubble& c_bubble = dynamic_cast <Bubble&> (bubble);


        ResourceManager::getInstance().getSound(COLLECT_SOUND);
		c_bubble.gotEaten(true);

        c_fish.setState(std::make_unique<ProtectedFishState>());
    }

    void fishWithFishHook(GameObject& fish, GameObject& fishHook)
	{
		Fish& c_fish = dynamic_cast <Fish&> (fish);
		FishHook& c_fishHook = dynamic_cast <FishHook&> (fishHook);

        c_fish.handleCollisions(c_fishHook);
	}

    void fishWithShell(GameObject& fish, GameObject& shell)
    {
        Fish& c_fish = dynamic_cast <Fish&> (fish);
        Shell& c_shell = dynamic_cast <Shell&> (shell);

        ResourceManager::getInstance().getSound(COLLECT_SOUND);
        c_shell.gotEaten(true);
        c_fish.setLife(1);

    }


    using collisionFunc = void (*) (GameObject& object1, GameObject& object2);
    using CollisionMap = std::unordered_map<std::string, collisionFunc>;

    //lookup-table
    std::unique_ptr<CollisionMap> CreateMap() {
        std::unique_ptr<CollisionMap> cm = std::make_unique<CollisionMap>();

        (*cm)[std::string(typeid(Fish).name()) + std::string(typeid(SmallFish).name())] = FishWithSmallFish;
        (*cm)[std::string(typeid(Fish).name()) + std::string(typeid(MediumFish).name())] = FishWithOtherFish<MediumFish>;
        (*cm)[std::string(typeid(Fish).name()) + std::string(typeid(BigFish).name())] = FishWithOtherFish<BigFish>;
        (*cm)[std::string(typeid(Fish).name()) + std::string(typeid(Shark).name())] = FishWithShark;
        (*cm)[std::string(typeid(Fish).name()) + std::string(typeid(JellyFish).name())] = FishWithJellyFish;

        (*cm)[std::string(typeid(Fish).name()) + std::string(typeid(Coral).name())] = FishWithCoral;
        (*cm)[std::string(typeid(Fish).name()) + std::string(typeid(Stone).name())] = FishWithStone;
        (*cm)[std::string(typeid(Fish).name()) + std::string(typeid(Anchor).name())] = fishWithAnchor;
        (*cm)[std::string(typeid(Fish).name()) + std::string(typeid(Key).name())] = FishWithKey;
        (*cm)[std::string(typeid(Fish).name()) + std::string(typeid(Treasure).name())] = FishWithTreasure;
        (*cm)[std::string(typeid(Fish).name()) + std::string(typeid(Bottle).name())] = FishWithBottle;
        (*cm)[std::string(typeid(Fish).name()) + std::string(typeid(Bubble).name())] = fishWithBubble;
        (*cm)[std::string(typeid(Fish).name()) + std::string(typeid(Shell).name())] = fishWithShell;

        (*cm)[std::string(typeid(SmallFish).name()) + std::string(typeid(Stone).name())] = OtherFishWithStone<SmallFish>;
		(*cm)[std::string(typeid(MediumFish).name()) + std::string(typeid(Stone).name())] = OtherFishWithStone<MediumFish>;
		(*cm)[std::string(typeid(BigFish).name()) + std::string(typeid(Stone).name())] = OtherFishWithStone<BigFish>;
		(*cm)[std::string(typeid(Shark).name()) + std::string(typeid(Stone).name())] = OtherFishWithStone<Shark>;
		(*cm)[std::string(typeid(JellyFish).name()) + std::string(typeid(Stone).name())] = OtherFishWithStone<JellyFish>;

        (*cm)[std::string(typeid(MediumFish).name()) + std::string(typeid(MediumFish).name())] = OtherFishWithOtherFish < MediumFish>;
        (*cm)[std::string(typeid(BigFish).name()) + std::string(typeid(BigFish).name())] = OtherFishWithOtherFish < BigFish>;
        (*cm)[std::string(typeid(Shark).name()) + std::string(typeid(Shark).name())] = OtherFishWithOtherFish < Shark>;
        (*cm)[std::string(typeid(SmallFish).name()) + std::string(typeid(SmallFish).name())] = OtherFishWithOtherFish < SmallFish>;
        (*cm)[std::string(typeid(Fish).name()) + std::string(typeid(FishHook).name())] = fishWithFishHook;

        return cm;
    }

    //function to return which the name of the objects prosses collisions resived
    collisionFunc lookup(const std::string& object1, const std::string& object2)
    {
        static std::unique_ptr<CollisionMap> map = CreateMap();
        std::string name = object1 + object2;
        auto itr = map->find(object1 + object2);
        if (itr == map->end())
            return nullptr;
        return itr->second;
    }


    void processCollision(GameObject& object1, GameObject& object2)
    {
        collisionFunc p2f = lookup(typeid(object1).name(), typeid(object2).name());
        if (p2f) {
            p2f(object1, object2);
        }
    
    }
}