#pragma once

#include <components/Component.hpp>



namespace ARCS {

struct LoDComponent : public Component
{
    explicit LoDComponent(int entID)
        : Component(entID)
    { };

    bool activeBehaviour { false };
    bool activeMovement  { false };

    float time2Execute    { lowAIExecution };
    float accumulatedTime { 0.0f };

    static float lowAIExecution;
    static float mediumAIExecution;

    static float shortDistance;
    static float middleDistance;
};

} // namespace ARCS