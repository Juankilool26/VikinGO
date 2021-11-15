#pragma once

#include <components/Component.hpp>
#include <SchedulingAI/FrequencyScheduler.hpp>



namespace ARCS {

struct SchedulingComponent : public Component
{
    explicit SchedulingComponent(int entID)
        : Component(entID)
    { };

    SCH::FrequencyScheduler scheduler { };
};

} // namespace ARCS