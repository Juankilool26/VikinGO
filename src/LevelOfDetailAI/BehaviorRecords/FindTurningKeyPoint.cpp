#include "FindTurningKeyPoint.hpp"



namespace LOD {


bool
FindTurningKeyPoint::isValid(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map)  {
    return ( !ai.inPatrol  &&  mr.isMemoryEmpty() );
}




void
FindTurningKeyPoint::enter(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map) {

}




void
FindTurningKeyPoint::exit(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map) {
    ai.moving = ai.pointing = false;
}



} // namespace LOD