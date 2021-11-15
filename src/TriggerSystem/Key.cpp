#include "Key.hpp"
#include <facade/Sound/ManFacadeSound.hpp>
#include <system/InputSystem.hpp>

Key::Key(int t,int p, int d, int idKey)
    : LimitedTrigger(t,p)
    , entDoor { d }
{ 
    id = idKey;
}

bool
Key::Try(ARCS::GameContext& gc, ARCS::CollisionSystem& cs, float delta){
    auto* player { gc.getEntityById(gc.getInputComponents()[0].getEntityID()) };
    auto* key    { gc.getEntityById(entID) };

    if( taked ) {
        if (ManFacadeInput::GetInstance()->getFacade()->isKeyPressed(static_cast<int>(KeyCode::KEY_KEY_Z)))
            ManFacadeRender::GetInstance()->getFacade()->clearTextKey(id);
    } else {
        key->pos->rotation.y += Trigger::animationSpeed * delta;
    }

    if(intersects(cs,key->pos->position ,*player)){
        if(taked)
            ManFacadeRender::GetInstance()->getFacade()->interInit();

        if(!taked){
            ManFacadeSound::GetInstance()->getFacade()->startEvent(KeySound::Efectos_take_key);
            
            //std::printf("The key was taken\n");
            taked = true;
            boxRootRangeTrigger.collided = false;
            key->col->boxRoot.box = {{0, 0, 0},{0, 0, 0}};
            boxRootRangeTrigger.box = {{-2, -2, -2},{2, 2, 2}};
            ManFacadeRender::GetInstance()->getFacade()->setNoVisible(entID);
            entID = entDoor;

            //Draw key HUD
            ManFacadeRender::GetInstance()->getFacade()->keyHUD(id);
            ManFacadeRender::GetInstance()->getFacade()->textKey(id);

            //ManFacadeRender::GetInstance()->getFacade()->clearTextKey(id);

        } else if(ManFacadeInput::GetInstance()->getFacade()->isKeyPressed(static_cast<int>(KeyCode::KEY_KEY_X))){
            //std::printf("The door was opened\n");
            key->col->boxRoot.box = {{0, 0, 0},{0, 0, 0}};
            ManFacadeRender::GetInstance()->getFacade()->setNoVisible(entID);
            lifeTime = -1;

            //Clean key HUD
            ManFacadeRender::GetInstance()->getFacade()->clearTextKey(id);
            ManFacadeRender::GetInstance()->getFacade()->clearKeyHUD(id);
            ManFacadeSound::GetInstance()->getFacade()->startEvent(KeySound::Efectos_door);
        }

       // gc.destroyEntityById(entID);
    }    
         

    return false;
}