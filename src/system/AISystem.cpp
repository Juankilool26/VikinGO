#include "AISystem.hpp"
#include <manager/GameContext.hpp>
#include <algorithm>




namespace ARCS {



bool AISystem::update(GameContext& gc, float dt) const {
    auto& aiCmpVec { gc.getAIComponents() };
    
    for (auto& ai : aiCmpVec) {

        auto* pos { gc.getPositionComponentByID( ai.getEntityID() ) };
        auto* phy { gc.getPhysicsComponentByID ( ai.getEntityID() ) };
        if ( !pos || !phy ) continue;
        

        phy->speedAngularVector.y = 0;
        phy->speedLinearVector.x = phy->speedLinearVector.y = phy->speedLinearVector.z = 0;


        // Apply movement Level of Detail
        const auto* lodcmp { gc.getLoDComponentByID(ai.getEntityID()) };
        if ( lodcmp && !lodcmp->activeMovement ) continue;

    
        if ( ai.pointing ) {

            // AI rotation
            auto vtx = ai.target.x - pos->position.x;
            auto vtz = ai.target.z - pos->position.z;

            auto targetOrien { glm::atan(vtz, vtx) };
            if ( targetOrien < 0 ) targetOrien += 2*PI;

            double angularDistance { targetOrien + glm::radians(pos->rotation.y) };
            if ( angularDistance >= PI ) angularDistance -= 2*PI;

            if      ( angularDistance >  ai.kMaxAMov ) phy->speedAngularVector.y = -1;
            else if ( angularDistance < -ai.kMaxAMov ) phy->speedAngularVector.y = +1;

            phy->speedLinearVector.y = 1;

        }
    

        if ( !ai.moving ) continue;

        // AI movement
        phy->speedLinearVector.x = 1;
        phy->speedLinearVector.y = 1;
        
    }

    return true;
}




} // namespace ARCS