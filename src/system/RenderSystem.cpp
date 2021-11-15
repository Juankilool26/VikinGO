#include <manager/GameContext.hpp>
#include <facade/Physics/ManFacadePhysics.hpp>
#include <facade/Input/ManFacadeInput.hpp>
#include <facade/Sound/ManFacadeSound.hpp>
#include "RenderSystem.hpp"

namespace ARCS {

RenderSystem::RenderSystem() {
    manFacadeRender = ManFacadeRender::GetInstance();
}

RenderSystem::~RenderSystem() {
    delete manFacadeRender;
    delete ManFacadeInput::GetInstance();
    delete ManFacadePhysics::GetInstance();
    delete ManFacadeSound::GetInstance();
    manFacadeRender = 0;
}

bool
RenderSystem::isDeviceRunning() {
    return manFacadeRender->getFacade()->isDeviceRunning();
}

void
RenderSystem::dropDevice(){
    manFacadeRender->getFacade()->dropDevice();
}

bool
RenderSystem::update(GameContext &gc, float deltatime, bool triggerActivate) {
    if ( !triggerActivate ) {
        if(timetoChangeFrame > kMaxAnim){
            auto& renderAnimComp = gc.getRenderComponents();
            for(auto& r : renderAnimComp) {
                if(r.animated) manFacadeRender->getFacade()->updateAnimation(r.getEntityID());
            }
            changePrivateTime();
        }
        incrementDeltatime(deltatime);
    }
    return manFacadeRender->getFacade()->update();
}

void RenderSystem::cleanScene(){
    manFacadeRender->getFacade()->cleanScene();
}


} // namespace ARCS