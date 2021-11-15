#include "ChasePlayer.hpp"



namespace LOD {



bool
ChasePlayer::isValid(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map)  {
    return ( !mr.isMemoryEmpty()  &&  !wp.hiting );
}




void
ChasePlayer::enter(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map) {

}




void
ChasePlayer::exit(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map) {
    ai.moving = ai.pointing = false;
}




} // namespace LOD