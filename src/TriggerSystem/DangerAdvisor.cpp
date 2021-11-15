#include "DangerAdvisor.hpp"
#include <facade/Sound/ManFacadeSound.hpp>

DangerAdvisor::DangerAdvisor(int p, KeySound s)
    :   RespawningTrigger(p)
    ,   key { s }
{
    updatesBetweenRespawns = 300;
}

bool
DangerAdvisor::Try(ARCS::GameContext& gc, ARCS::CollisionSystem& cs, float delta) {
    auto* player = gc.getEntityById(gc.getInputComponents()[0].getEntityID());

    if(isActive() && intersects(cs,gc.getEntityById(entID)->pos->position ,*player)) {
        ManFacadeSound::GetInstance()->getFacade()->startEvent(key);
        boxRootRangeTrigger.collided = false;
        Desactivate();
    }

    return false;
}