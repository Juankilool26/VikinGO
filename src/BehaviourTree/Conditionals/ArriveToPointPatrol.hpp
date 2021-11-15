#pragma once

#include <BehaviourTree/BehaviourTree/Node.hpp>


struct ArriveToPointPatrol : Node
{
    bool run(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map) override;
};