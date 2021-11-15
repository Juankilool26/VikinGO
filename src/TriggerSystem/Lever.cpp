#include "Lever.hpp"
#include <facade/Sound/ManFacadeSound.hpp>


Lever::Lever(int p, int d)
    : RespawningTrigger(p)
    , entDoor { d }
{
    updatesBetweenRespawns = 300;
}

bool
Lever::Try(ARCS::GameContext& gc, ARCS::CollisionSystem& cs, float delta) {
    auto* player = gc.getEntityById(gc.getInputComponents()[0].getEntityID());

    if(isActive() && intersects(cs,gc.getEntityById(entID)->pos->position ,*player)){
        ManFacadeRender::GetInstance()->getFacade()->interInit();
        ManFacadeSound::GetInstance()->getFacade()->startEvent(KeySound::Efectos_lever);
    
        if(!actioned && ManFacadeInput::GetInstance()->getFacade()->isKeyPressed(static_cast<int>(KeyCode::KEY_KEY_X))){ // TODO: Incluir la compropacion de tecla pulsada
            // TODO: AQUI LO QUE TIENE QUE HACER
            //std::printf("accionando el puente \n"); 
            //gc.getEntityById(entDoor)->col->boxRoot.box = {{0,0,0},{0,0,0}};
            gc.getEntityById(entDoor)->col->mask = ARCS::CollisionComponent::L_NoLayer;
            ManFacadeRender::GetInstance()->getFacade()->setNoVisible(entDoor);
            gc.getPositionComponentByID(entID)->rotation.y -= 180;
            actioned = true;
            Desactivate();
        }
        else if( actioned && ManFacadeInput::GetInstance()->getFacade()->isKeyPressed(static_cast<int>(KeyCode::KEY_KEY_X))){
            //std::printf("accionando el puente 2 \n"); 
            gc.getEntityById(entDoor)->col->boxRoot.box = {{-1,-1,-1},{1,1,1}};
            ManFacadeRender::GetInstance()->getFacade()->setVisible(entDoor);
            gc.getPositionComponentByID(entID)->rotation.y += 180;
            actioned = false;
            Desactivate();
        } 
    }
    return false;
}