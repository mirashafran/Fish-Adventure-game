#pragma once
#include "NormalFishState.h"

//class Fish;

class ProtectedFishState : public FishState
{
public:
    ProtectedFishState() {}
	~ProtectedFishState() = default;
    void update(Fish& fish) override;
    void onEnter(Fish& fish) override;
    void onExit(Fish& fish) override;
    void handleCollision(Fish& fish, GameObject& other) override;

private:
    sf::Clock m_protectionClock;
};