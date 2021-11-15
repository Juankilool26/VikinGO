#include "PlayerIsInactive.hpp"


bool
PlayerIsInactive::run(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map)
{
    return !wp.hiting;
}
