#include "GoToNextPointPatrol.hpp"



namespace LOD {



bool
GoToNextPointPatrol::isValid(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map)  {
    return (
            mr.isMemoryEmpty()
        &&  glm::distance(pos.position, ai.pointsPatrol[ai.actualPoint])  <=  ai.kMinRange2Stop
        &&  ai.inPatrol
    );
}




void
GoToNextPointPatrol::enter(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map) {
    ai.target = ai.pointsPatrol[ai.actualPoint];
}




void
GoToNextPointPatrol::exit(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map) {
    ai.moving = ai.pointing = false;
}



} // namespace LOD