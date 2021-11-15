#include "KeepWalking.hpp"


bool
KeepWalking::run(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map)
{
    ai.target = ai.pointsPatrol[ai.actualPoint];
    ai.pointing = ai.moving = true;
    
    return true;
}
