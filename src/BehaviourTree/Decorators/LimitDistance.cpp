#include "LimitDistance.hpp"



bool
LimitDistance::run(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map) {
    bool lod { false };
/*
    // Choose speed AI behavior
    float distance { glm::distance(pos.position, playerPos) };
    if ( distance < shortDistance )
        time2Execute = 0;
    else if ( distance >= shortDistance  &&  distance < middleDistance )
        time2Execute = mediumAIExecution;
    else
        time2Execute = lowAIExecution;

    accumulatedTime += dt;
    if ( accumulatedTime >= time2Execute ) {
        accumulatedTime = 0;
        lod = child->run(mr, pos, ai, wp, map);
    }
*/
    return lod;
}