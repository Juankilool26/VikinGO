#include <manager/GameContext.hpp>
#include "LoDSystem.hpp"




namespace ARCS {



bool
LoDSystem::update(GameContext& gc, float dt) const noexcept {
    auto& lodCmpVec { gc.getLoDComponents() };
    auto& player    { gc.getPlayer() };


    for (auto& lodcmp : lodCmpVec) {

        const auto* poscmp { gc.getPositionComponentByID(lodcmp.getEntityID()) };
        if ( !poscmp ) continue;

        lodcmp.activeBehaviour = lodcmp.activeMovement = false;


        // Choose speed AI execution depending on distance
        float distance { glm::distance(poscmp->position, player.pos->position) };
        if ( distance < lodcmp.shortDistance ) {
            lodcmp.time2Execute = 0;
            lodcmp.activeMovement = true;
        } else if ( distance >= lodcmp.shortDistance  &&  distance < lodcmp.middleDistance ) {
            lodcmp.time2Execute = lodcmp.mediumAIExecution;
            lodcmp.activeMovement = true;
        } else {
            lodcmp.time2Execute = lodcmp.lowAIExecution;
        }


        // Set accumulatedTime
        lodcmp.accumulatedTime += dt;
        if ( lodcmp.accumulatedTime >= lodcmp.time2Execute ) {
            lodcmp.accumulatedTime = 0;
            lodcmp.activeBehaviour = true;
        }

    }
    

    return true;
}



} // namespace ARCS