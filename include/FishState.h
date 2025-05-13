#pragma once
#include "GameObject.h"
#include "Shark.h"
#include "SmallFish.h"
#include "BigFish.h"
#include "MediumFish.h"
#include "JellyFish.h"
#include "Stone.h"
#include "Anchor.h"
#include "FishHook.h"
#include "ResourceManager.h"

class Fish;

class FishState
{
public:
    virtual ~FishState() = default;
    virtual void update(Fish& fish) = 0;
    virtual void onEnter(Fish& fish) = 0;
    virtual void onExit(Fish& fish) = 0;
    virtual void handleCollision(Fish& fish, GameObject& other) = 0;
};