#include <algorithm>
#include <glm/glm.hpp>
#include <system/PhysicsSystem.hpp>
#include <manager/GameContext.hpp>




namespace ARCS {



bool PhysicsSystem::update(GameContext& gc, float dt) const {
    auto& phyCmpVec { gc.getPhysicsComponents() };

    for (auto& phy : phyCmpVec) {
        auto* pos { gc.getPositionComponentByID( phy.getEntityID() ) };

        // Update rotation
        pos->rotation.y += phy.speedAngularVector.y * phy.speedAngular * dt;
        if      ( pos->rotation.y > 360 )  pos->rotation.y -= 360;
        else if ( pos->rotation.y < 0   )  pos->rotation.y += 360;

        float directionX = 0;
        float directionZ = 0;


        auto calculatePositionX = [&](int sense_, float angle_) {
            directionX += sense_*glm::cos( glm::radians(angle_) );
            directionZ += sense_*glm::sin( glm::radians(angle_) );
        };

        auto calculatePositionZ = [&](int sense_, float angle_) {
            directionX += sense_*glm::sin( glm::radians(angle_) );
            directionZ += sense_*glm::cos( glm::radians(angle_) );
        };



        // Orientation for ai entities while rotating
        if ( phy.speedLinearVector.y  &&  !phy.speedLinearVector.x  &&  gc.getEntityById(phy.getEntityID())->ai ) {
            calculatePositionX(1, -pos->rotation.y);
            phy.speedDisplacementVector.x = directionX;
            phy.speedDisplacementVector.z = directionZ;
            continue;
        }

        // Orientation and movement
        if ( phy.speedLinearVector.x == 1 )
            calculatePositionX(1, -pos->rotation.y);
        else if ( phy.speedLinearVector.x == -1 )
            calculatePositionX(-1, -pos->rotation.y);

        if ( phy.speedLinearVector.z == 1 )
            calculatePositionZ(1, pos->rotation.y);
        else if ( phy.speedLinearVector.z == -1 )
            calculatePositionZ(-1, pos->rotation.y);


        // Calculate acceleration
        if ( phy.speedLinearVector.y ) {                        // TODO: esto puede valor 0, el enemigo no ataca, mirar AISys
            phy.acceleration += phy.accIncrement*dt;
            phy.speedDisplacementVector.x = directionX;
            phy.speedDisplacementVector.z = directionZ;
        } else {
            phy.acceleration -= phy.accIncrement*dt;
        }

        phy.acceleration = std::clamp(phy.acceleration, 0.0f, 1.0f);


        // Update position
        pos->position.x += phy.speedLinear * phy.speedDisplacementVector.x * dt * phy.acceleration;
        pos->position.z += phy.speedLinear * phy.speedDisplacementVector.z * dt * phy.acceleration;
    }
   
    return true;
}




} // namespace ARCS