#include "CameraSystem.hpp"
#include <glm/glm.hpp>
#include <manager/GameContext.hpp>
#include <algorithm>

#include <facade/Physics/ManFacadePhysics.hpp>

namespace ARCS {



CameraSystem::CameraSystem() :
    manFacadeRender { ManFacadeRender::GetInstance() }
{ }




CameraSystem::~CameraSystem() {
    manFacadeRender = 0;
}




bool
CameraSystem::update(GameContext &gc) const noexcept {
    auto& camCmpVec { gc.getCameraComponents() };
    
    for (auto& cam : camCmpVec) {
        PositionComponent* posCam { gc.getPositionComponentByID( cam.getEntityID() ) };
        if (!posCam) continue;

        PositionComponent* posNode { gc.getPositionComponentByID( cam.followEntityID ) };
        if (!posNode) {

            // Destroy camera when player dies
            gc.destroyEntityById( cam.getEntityID() );
            continue;
        }

        // Calculate camera position
        cam.direction.x = glm::cos( glm::radians(-posNode->rotation.y) );
        cam.direction.z = glm::sin( glm::radians(-posNode->rotation.y) );
        posCam->position.x = posNode->position.x + cam.direction.x * cam.getRelativeDistance();
        posCam->position.z = posNode->position.z + cam.direction.z * cam.getRelativeDistance();

        ManFacadePhysics::GetInstance()->getFacade()->update( *posCam );

        // Calculate camera target
        glm::vec3 distCamObj = posCam->position - posNode->position;
        cam.lookat.x = posNode->position.x + 2*distCamObj.x;
        cam.lookat.z = posNode->position.z + 2*distCamObj.z;

        cam.direction.y = std::clamp(cam.direction.y, -cam.kLimitTargetY, cam.kLimitTargetY);
        cam.lookat.y = posNode->position.y + 2*distCamObj.y + cam.direction.y;

        manFacadeRender->getFacade()->setCameraTarget( cam );
    }

    return true;
}



} // namespace ARCS
