#include "VisualDepurationSystem.hpp"
#include <glm/glm.hpp>
#include <manager/GameContext.hpp>
#include <util/KeyCodes.hpp>
#include <algorithm>



namespace ARCS {



VisualDepurationSystem::VisualDepurationSystem() :
    manFacadeRender  { ManFacadeRender::GetInstance()  },
    manFacadePhysics { ManFacadePhysics::GetInstance() },
    manFacadeInput   { ManFacadeInput::GetInstance()   }
    
{ }




VisualDepurationSystem::~VisualDepurationSystem() {
    manFacadeRender  = nullptr;
    manFacadeInput   = nullptr;
    manFacadePhysics = nullptr;
}




bool
VisualDepurationSystem::update(GameContext &gc, float dt) noexcept {
    auto& visDepVec { gc.getVisualDepurationComponents() };


    // Set visual depuration
    if ( activeMode )
        for (auto& vd : visDepVec) setVisualObjectsPosition(gc, vd);

    // Update
    if ( time2Activate > kMaxTime2Activate  &&  manFacadeInput->getFacade()->isKeyPressed( static_cast<int>(KeyCode::KEY_F9) )) {
        activeMode = !activeMode;
        for (auto& vd : visDepVec) {
            for (auto& visID : vd.visualID)
                manFacadeRender->getFacade()->setVisible(visID, activeMode);
            setVisualObjectsPosition(gc, vd);
        }
        time2Activate = 0;
    }
    time2Activate += dt;


    return activeMode;
}





void
VisualDepurationSystem::setVisualObjectsPosition(GameContext &gc,const VisualDepurationComponent& vdcmp) noexcept {
    const auto* wpcmp  { gc.getWeaponComponentByID(vdcmp.getEntityID())              };
    const auto* poscmp { gc.getPositionComponentByID(vdcmp.getEntityID())            };
    const auto* sencmp { gc.getSensorialPerceptionComponentByID(vdcmp.getEntityID()) };

    if ( wpcmp && poscmp )
        manFacadePhysics->getFacade()->setMeshPosition( vdcmp.visualID[0], poscmp->position + wpcmp->wpositionRelative );

    if ( sencmp ) {
        manFacadePhysics->getFacade()->setMeshPosition( vdcmp.visualID[1], poscmp->position + vdcmp.visualPos[1] );
        manFacadePhysics->getFacade()->setMeshRotation( vdcmp.visualID[1], poscmp->rotation + vdcmp.visualPos[1] );
        manFacadePhysics->getFacade()->setMeshPosition( vdcmp.visualID[2], poscmp->position + vdcmp.visualPos[2] );
        manFacadePhysics->getFacade()->setMeshPosition( vdcmp.visualID[3], poscmp->position + sencmp->rSense.vision.positionRelative );
    }
}






} // namespace ARCS
