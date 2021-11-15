#include "ActivatorTrigger.hpp"
#include <manager/GameContext.hpp>
#include <facade/Render/ManFacadeRender.hpp>



ActivatorTrigger::ActivatorTrigger(int p, Trigger& t) :  RespawningTrigger(p), activate{t}
{
    activateEnt = t.entID;
    t.setInactive();
    ManFacadeRender::GetInstance()->getFacade()->setNoVisible(activate.entID);
    updatesBetweenRespawns = 6.0;
}




bool
ActivatorTrigger::Try(ARCS::GameContext& gc, ARCS::CollisionSystem& cs, float) {
    if(activate.entID == activateEnt){
        auto* player = gc.getEntityById(gc.getInputComponents()[0].getEntityID());
        if(isActive() && intersects(cs,gc.getEntityById(entID)->pos->position ,*player))
            ManFacadeRender::GetInstance()->getFacade()->interInit();
        if(isActive() && intersects(cs,gc.getEntityById(entID)->pos->position ,*player) && ManFacadeInput::GetInstance()->getFacade()->isKeyPressed(static_cast<int>(KeyCode::KEY_KEY_X))){ 
            activate.setActive();
            ManFacadeRender::GetInstance()->getFacade()->setVisible(activate.entID);
            Desactivate();
        } else if (isActive()){
            ManFacadeRender::GetInstance()->getFacade()->setNoVisible(activate.entID);
            activate.setInactive();
        }
    }
    else
        setToBeRemoved();

    return false;
}