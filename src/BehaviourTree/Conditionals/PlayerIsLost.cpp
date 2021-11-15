#include "PlayerIsLost.hpp"



bool
PlayerIsLost::run(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map)
{   
    return ( !ai.inPatrol  &&  mr.isMemoryEmpty() );
}