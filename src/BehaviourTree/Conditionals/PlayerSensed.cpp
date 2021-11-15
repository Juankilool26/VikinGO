#include "PlayerSensed.hpp"


bool
PlayerSensed::run(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map)
{
    return !mr.isMemoryEmpty();
}