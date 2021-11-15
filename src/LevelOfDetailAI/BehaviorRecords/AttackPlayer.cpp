#include "AttackPlayer.hpp"



namespace LOD {



bool
AttackPlayer::isValid(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map)  {
    return ( !mr.isMemoryEmpty()  &&  mr.hittable );
}




void
AttackPlayer::enter(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map) {
    wp.hiting = true;
    ai.moving = false;
}




void
AttackPlayer::exit(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map) {
    wp.hiting = false;
}




} // namespace LOD