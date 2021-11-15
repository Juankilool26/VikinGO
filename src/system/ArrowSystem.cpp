#include <manager/GameContext.hpp>
#include "ArrowSystem.hpp"



namespace ARCS {




ArrowSystem::ArrowSystem()
    :   manFacadeRender { ManFacadeRender::GetInstance() }
{ }




ArrowSystem::~ArrowSystem() {
    manFacadeRender = nullptr;
}




bool
ArrowSystem::update(GameContext& gc, float delta) const noexcept {
    auto& arrVecCmp { gc.getArrowComponents() };


    for (auto& arr : arrVecCmp) {
        if ( !arr.active ) continue;
        
        auto* arrowPos { gc.getPositionComponentByID(arr.arrowID) };
        auto* wpcmp    { gc.getWeaponComponentByID(arr.arrowID)   };
        const auto* archerPos { gc.getPositionComponentByID(arr.getEntityID()) };
        const auto* aicmp { gc.getAIComponentByID(arr.getEntityID()) };
        if ( !wpcmp  ||  !arrowPos  ||  !archerPos  ||  !aicmp ) continue;


        // Calculate flight time and displacement
        float radiansY { glm::radians(arr.angle.y) };
        if (arr.flightTime > 0.0f) {

            arr.accumulatedTime += delta;

        } else {

            // Prepare arrow throw
            arrowPos->position = archerPos->position;
            wpcmp->hiting = true;
            manFacadeRender->getFacade()->setVisible( arr.arrowID );

            // Displacement
            arr.displacement.x = aicmp->target.x - archerPos->position.x;
            arr.displacement.z = aicmp->target.z - archerPos->position.z;
            arr.displacement  *= delta;

            // Orientation
            arrowPos->rotation.y = archerPos->rotation.y;
            arr.angle.z = glm::atan( arr.displacement.z / arr.displacement.x );
            arr.angle.x = ARCS::PI - arr.angle.x;
            //if ( (arr.displacement.x >= 0 && arr.displacement.z < 0)  ||  (arr.displacement.x >= 0 && arr.displacement.z >= 0) ) {
            //    arr.angle.z = glm::atan( arr.displacement.z / arr.displacement.x );
            //    arr.angle.x = ARCS::PI - arr.angle.x;
            //} else {
            //    arr.angle.x = glm::atan( arr.displacement.z / arr.displacement.x );
            //    arr.angle.z = ARCS::PI - arr.angle.x;
            //}
            

            // Flight time
            arr.flightTime = arrowPos->position.y + (2 * glm::pow(glm::sin(radiansY), 2) * arr.velocity / arr.gravity);

        }

        
        // Set arrow displacement and height
        if (arrowPos->position.y > arr.floorHeight) {

            // Displacement
            arrowPos->position.x += arr.displacement.x;
            arrowPos->position.z += arr.displacement.z;
            arrowPos->position.y  = archerPos->position.y + (arr.velocity*glm::sin(radiansY)*arr.accumulatedTime) - (0.5*arr.gravity*glm::pow(arr.accumulatedTime, 2));

            // Orientation
            glm::vec3 velocity { 
                    arr.velocity*glm::cos(arr.angle.x)
                ,   arr.velocity*glm::sin(radiansY) - arr.gravity*arr.accumulatedTime
                ,   arr.velocity*glm::cos(arr.angle.z)
            };
            arrowPos->rotation.x = glm::degrees(glm::atan( velocity.y / velocity.x ));
            arrowPos->rotation.z = glm::degrees(glm::atan( velocity.y / velocity.z ));

        } else {

            wpcmp->hiting = arr.active = false;
            //manFacadeRender->getFacade()->setNoVisible( arr.arrowID );

        }
    }


    return true;
}



} // namespace ARCS