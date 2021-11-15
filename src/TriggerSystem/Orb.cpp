#include "Orb.hpp"
#include <facade/Sound/ManFacadeSound.hpp>



Orb::Orb(int t,int p, int d)
    : LimitedTrigger(t,p)
    , entDoor { d }
{ 
    ManFacadeRender::GetInstance()->getFacade()->setNoVisible(d);
}

bool
Orb::Try(ARCS::GameContext& gc, ARCS::CollisionSystem& cs, float delta){
    auto* player = gc.getEntityById(gc.getInputComponents()[0].getEntityID());
    auto* orb { gc.getEntityById(entID) };
    if ( !orb ) return false;

    //if(taked && ManFacadeInput::GetInstance()->getFacade()->isKeyPressed(static_cast<int>(KeyCode::KEY_KEY_Z))){
        //ManFacadeRender::GetInstance()->getFacade()->clearTextOrb();
    //}

    if(isActive()) {

        // Animate orb
        orb->pos->rotation.y += Trigger::animationSpeed * delta;

        if(!taked && intersects(cs,orb->pos->position ,*player)){
            ManFacadeSound::GetInstance()->getFacade()->startEvent(KeySound::Efectos_orb);
            //std::printf("The key was taken\n");
            taked = true;
            boxRootRangeTrigger.collided = false;
            orb->col->boxRoot.box = {{0,0,0},{0,0,0}};
            boxRootRangeTrigger.box = {{-2,-2,-2},{2,2,2}};
            ManFacadeRender::GetInstance()->getFacade()->setNoVisible(entID);
            entID = entDoor;
            ManFacadeRender::GetInstance()->getFacade()->setVisible(entID);
            //std::printf("The door was opened\n");
            gc.getEntityById(entID)->col->boxRoot.box = {{0,0,0},{0,0,0}};        
            lifeTime = -1;

            //Draw orb HUD
            ManFacadeRender::GetInstance()->getFacade()->orbHUD();
            //ManFacadeRender::GetInstance()->getFacade()->textOrb();
        }
        //gc.destroyEntityById(entID);
    }
    return false;
}