#pragma once
#include "FishState.h"

class NormalFishState : public FishState
{
    public:
        void update(Fish& fish) override;
        void onEnter(Fish& fish) override;
        void onExit(Fish& fish) override;
        void handleCollision(Fish& fish, GameObject& other) override;

};