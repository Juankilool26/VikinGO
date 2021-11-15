#include "PlayerIsInFront.hpp"




bool
PlayerIsInFront::run(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map)
{
    return mr.hittable;
}
