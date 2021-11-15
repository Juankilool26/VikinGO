#include "GoToNextPointPatrol.hpp"


bool
GoToNextPointPatrol::run(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map)
{
    ++ai.actualPoint;
    if(ai.actualPoint > ai.pointsPatrol.size()-1) ai.actualPoint = 0;

    ai.target = ai.pointsPatrol[ai.actualPoint];
    ai.moving = ai.pointing = true;

    if(ai.pointsPatrol.size() <= 1)
        ai.moving = ai.pointing = false;        // FIXED: Esto para que es??
    
    return true;
}
