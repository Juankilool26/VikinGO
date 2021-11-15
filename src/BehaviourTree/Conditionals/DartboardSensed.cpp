#include "DartboardSensed.hpp"



bool
DartboardSensed::run(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map)
{
    if ( !mr.isMemoryEmpty() ) {
        ai.pointing = true;
        ai.target = mr.lastSensePosition;
    } else {
        ai.pointing = false;
    }

    return true;
}