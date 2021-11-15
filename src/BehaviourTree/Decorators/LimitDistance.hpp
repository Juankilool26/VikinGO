#pragma once

#include <BehaviourTree/BehaviourTree/Decorator.hpp>



struct LimitDistance : Decorator
{
    ~LimitDistance() = default;
    bool run(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map) override;
/* 
private:
    float time2Execute    { lowAIExecution };
    float accumulatedTime { 0.0f };

    inline static constexpr float lowAIExecution    { 4.f  };
    inline static constexpr float mediumAIExecution { 2.f  };

    inline static constexpr float shortDistance  { 10.f  };
    inline static constexpr float middleDistance { 20.f }; */
};
