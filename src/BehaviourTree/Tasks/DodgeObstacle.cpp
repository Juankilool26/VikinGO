#include "DodgeObstacle.hpp"


bool
DodgeObstacle::run(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map)
{
    ai.currentPointMapID = map.getClosestAuxPoint(pos.position);
    ai.target = map.getAuxPointByID(ai.currentPointMapID);
    ai.moving = ai.pointing = true;

    return true;
}