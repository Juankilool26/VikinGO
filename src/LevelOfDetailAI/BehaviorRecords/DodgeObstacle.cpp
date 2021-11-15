#include "DodgeObstacle.hpp"


namespace LOD {




bool
DodgeObstacle::isValid(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map)  {
    return ( !mr.isMemoryEmpty()  &&  ai.beetween );
}




void
DodgeObstacle::enter(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map) {

}




void
DodgeObstacle::exit(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map) {
    ai.moving = ai.pointing = false;
}




} // namespace LOD