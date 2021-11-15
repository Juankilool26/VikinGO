#include "Trap.hpp"
#include <facade/Sound/ManFacadeSound.hpp>



Trap::Trap(int t,int p)
    : LimitedTrigger(t,p)
{ 
  
}

bool
Trap::Try(ARCS::GameContext& gc, ARCS::CollisionSystem& cs, float delta){
    auto* player = gc.getEntityById(gc.getInputComponents()[0].getEntityID());

    //if(taked && ManFacadeInput::GetInstance()->getFacade()->isKeyPressed(static_cast<int>(KeyCode::KEY_KEY_Z))){
        //ManFacadeRender::GetInstance()->getFacade()->clearTextOrb();
    //}

    if(isActive() && intersects(cs,gc.getEntityById(entID)->pos->position ,*player)){
        if(!taked){
            ManFacadeSound::GetInstance()->getFacade()->startEvent(KeySound::Voces_hurt_main_women);
            ManFacadeSound::GetInstance()->getFacade()->startEvent(KeySound::Efectos_bearTrap);
            taked = true;
            --player->heal->health;
            ManFacadeRender::GetInstance()->getFacade()->drawHud(*player);
            boxRootRangeTrigger.collided = false;
            gc.getEntityById(entID)->col->boxRoot.box = {{0,0,0},{0,0,0}};
            ManFacadeRender::GetInstance()->getFacade()->setNoVisible(entID);      
            lifeTime = -1;

        }
        //gc.destroyEntityById(entID);
    }       
    return false;
}