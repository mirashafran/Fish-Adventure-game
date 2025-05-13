#include "FishHook.h"

FishHook::FishHook(const sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& size)
	: MovingObject(texture, position, size, 1, 0, 1, 1)
{
    m_hookState = Inactive;
    m_hookDelay = sf::seconds(7.0f); // Delay between actions
    m_hookFallCount = HOOK_FALLS_COUNT;
    m_maxHookFalls = MAX_HOOK_FALLS;
    m_hookXOffset = HOOK_X_OFFSET;
    m_speed = HOOK_FALL_DURATION;
}

//the hook movment animation
void FishHook::move(float deltaTime)
{
    switch (m_hookState)
    {
    case HookState::Inactive:
        if (m_hookState == Inactive && m_hookFallCount < m_maxHookFalls)
        {
            if (m_hookClock.getElapsedTime() >= m_hookDelay)
            {
                sf::Vector2f newHookStartPos = sf::Vector2f(HOOK_START_POS.x + m_hookXOffset, HOOK_START_POS.y + 300);
                startMoving(sf::Vector2f(HOOK_START_POS.x + m_hookXOffset, HOOK_START_POS.y), newHookStartPos, m_speed, false);

                m_hookState = Falling;
            }
        }
        break;

    case HookState::Falling:
        if (isFalling())
        {
            updateMoving(deltaTime);
        }
        else
        {
            //After the hook has fallen, it will ascend back up
            startMoving(getPosition(), sf::Vector2f(getPosition().x, getPosition().y - HOOK_Y_OFFSET), m_speed, true);
            m_hookState = Ascending;

        }
        break;

    case HookState::Ascending:
        if (isAscending())
        {
            updateMoving(deltaTime);
        }
        else
        {
            m_hookXOffset += OFFSET; // Increment the x offset by 300 units
            m_hookFallCount++;
            m_hookClock.restart();
            m_hookState = Inactive;
        }
        break;
    }
	
}




