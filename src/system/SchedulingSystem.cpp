#include <manager/GameContext.hpp>
#include "SchedulingSystem.hpp"


namespace ARCS {



SchedulingSystem::SchedulingSystem(SensoryMemory& memory)
    :   sMemory { memory }
{ }



bool
SchedulingSystem::update(GameContext& gc) const noexcept {
    auto& schCmpVec { gc.getSchedulingComponents() };
    auto& mapcmp    { gc.getMapComponent() };
    
    for (auto& schcmp : schCmpVec) {
        auto* entity { gc.getEntityById(schcmp.getEntityID()) };
        auto& memoryRecord { sMemory.getMemoryRecordFromMap(entity) };

        schcmp.scheduler.run(memoryRecord, *entity->arr, *entity->pos, *entity->ai, *entity->wc, mapcmp);
    }

    return true;
}



} // namespace ARCS