#include "KeepWalking.hpp"


namespace LOD {



bool
KeepWalking::isValid(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map)  {
    return (
            mr.isMemoryEmpty()
        &&  glm::distance(pos.position, ai.pointsPatrol[ai.actualPoint])  >  ai.kMinRange2Stop
        &&  ai.inPatrol
    );
}




void
KeepWalking::enter(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map) {
    ai.target = ai.pointsPatrol[ai.actualPoint];
}




void
KeepWalking::exit(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map) {
    ai.pointing = ai.moving = false;
}



} // namespace LOD