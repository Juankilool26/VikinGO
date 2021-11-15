#include "HealthRecover.hpp"
#include <facade/Sound/ManFacadeSound.hpp>



HealthRecover::HealthRecover(int t,int p)
    : LimitedTrigger(t,p)
{ }

bool
HealthRecover::Try(ARCS::GameContext& gc, ARCS::CollisionSystem& cs, float delta){
    auto* player  { gc.getEntityById(gc.getInputComponents()[0].getEntityID()) };
    auto* healRec { gc.getEntityById(entID) };

    if( player && healRec ) {

        // Animated trigger
        healRec->pos->rotation.y += Trigger::animationSpeed * delta;

        if(intersects(cs, healRec->pos->position, *player)) {
            ManFacadeSound::GetInstance()->getFacade()->startEvent(KeySound::Efectos_recover_health);  
            
            //std::printf("Recover Health\n");           
            boxRootRangeTrigger.collided = false;
            healRec->col->boxRoot.box = {{0,0,0},{0,0,0}};
            ManFacadeRender::GetInstance()->getFacade()->setNoVisible(entID);
            ManFacadeRender::GetInstance()->getFacade()->drawHud(*player);

            if(player->heal->health < player->heal->maxHP)
                ++player->heal->health;

            lifeTime = -1;
        }
    }
    return false;          
}