#pragma once
#include "FishState.h"

class DeadFishState : public FishState {
public:
    void update(Fish& fish) override;
    void onEnter(Fish& fish) override;
    void onExit(Fish& fish) override;
    void handleCollision(Fish& fish, GameObject& other) override;

private:
    sf::Clock m_clock;
};