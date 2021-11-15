#include "ArriveToPointPatrol.hpp"


bool
ArriveToPointPatrol::run(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map)
{
    return ( glm::distance(pos.position, ai.pointsPatrol[ai.actualPoint])  <=  ai.kMinRange2Stop );
}