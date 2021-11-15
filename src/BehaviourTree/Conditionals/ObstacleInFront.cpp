#include "ObstacleInFront.hpp"


bool
ObstacleInFront::run(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map)
{
    
    if(glm::distance(pos.position, map.getKeyPointByID(ai.currentPointMapID)) <= ai.kMinRange2Stop)
        ai.beetween = false;

    return ai.beetween;
}