#include "ConversationNPC.hpp"
#include <manager/GameContext.hpp>
#include <facade/Render/ManFacadeRender.hpp>

ConversationNPC::ConversationNPC(int p, KeySound key_, int idConv)
    : RespawningTrigger(p)
    , key { key_ }
{
    updatesBetweenRespawns = 9999999.f;
    id = idConv;
}

bool
ConversationNPC::Try(ARCS::GameContext& gc, ARCS::CollisionSystem& cs, float delta) {
    auto* player = gc.getEntityById(gc.getInputComponents()[0].getEntityID());
    auto* npc = gc.getEntityById(entID);
    
    if (timeTalking > kTimeLimit) {
        if(isActive() && intersects(cs,gc.getEntityById(entID)->pos->position ,*player))
            ManFacadeRender::GetInstance()->getFacade()->interInit();
            
        if(isActive() && intersects(cs,gc.getEntityById(entID)->pos->position ,*player) && ManFacadeInput::GetInstance()->getFacade()->isKeyPressed(static_cast<int>(KeyCode::KEY_KEY_X))){ // TODO: Incluir la compropacion de tecla pulsada
            ManFacadeSound::GetInstance()->getFacade()->set3DAttributes(key, npc->pos->position, player->pos->position, player->pos->rotation);
            ManFacadeSound::GetInstance()->getFacade()->startEvent(key);
            ManFacadeRender::GetInstance()->getFacade()->drawConver(id);
            talking = true;
            Desactivate();
            timeTalking = 0;
        } else if (ManFacadeInput::GetInstance()->getFacade()->isKeyPressed(static_cast<int>(KeyCode::KEY_KEY_X)) && talking){
            setActive();
            timeTalking = 0;
            ManFacadeSound::GetInstance()->getFacade()->stopEvent(key);
            ManFacadeRender::GetInstance()->getFacade()->clearConver();

            talking = false;
        }
    }

    return talking;
}