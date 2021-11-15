#include "ThrowArrow.hpp"



bool
ThrowArrow::run(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map)
{
    if ( !mr.isMemoryEmpty() ) {
        arr.active = true;
        arr.flightTime = 0;
        arr.accumulatedTime = 0;
    }
    return true;
}
