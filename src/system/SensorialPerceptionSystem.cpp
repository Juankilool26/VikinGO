#include <manager/GameContext.hpp>
#include "SensorialPerceptionSystem.hpp"
#include "CollisionSystem.hpp"





SensorialPerceptionSystem::SensorialPerceptionSystem(ARCS::CollisionSystem &cs, ARCS::GameContext &gc, SensoryMemory &sm, Arbiter &a): colsys{cs}, sensoryMemory{sm}, arbiter{a} {
    auto& sensCompVec= gc.getSensorialPerceptionComponents();
    notifications.reserve(sensCompVec.size());
    const ARCS::Entity* player = gc.getEntityById(gc.getInputComponents()[0].getEntityID());
    if(!player && !player->sens && !player->pos) return;

    for(auto& sensComp : sensCompVec){
        
        if(player->id != sensComp.getEntityID()){
            ARCS::Entity* enemy = gc.getEntityById(sensComp.getEntityID());
            notifications.emplace_back(*enemy,sensComp.rSense,player->sens->rSense.noise,player->col->boxRoot,player->pos->position,enemy->pos->position);  
        }
    }
}

SensorialPerceptionSystem::~SensorialPerceptionSystem(){
    notifications.clear();
    
}

bool SensorialPerceptionSystem::update(ARCS::GameContext &gc, float dt){

    auto& sensCompVec= gc.getSensorialPerceptionComponents();
    for(auto& sensComp : sensCompVec){
        auto* ent = gc.getEntityById(sensComp.getEntityID());

        if(ent  &&  ent->phy){
            sensComp.rSense.vision.positionRelative.x = 5 * ent->phy->speedDisplacementVector.x;
            sensComp.rSense.vision.positionRelative.z = 5 * ent->phy->speedDisplacementVector.z;
        }
    }
    
    check(gc,dt); // check collsion perception fot detect player

    return true;
}

void SensorialPerceptionSystem::check(ARCS::GameContext &gc, float dt){
    std::vector<ARCS::Entity*> enemies;
    enemies.reserve(20);                    // FIXED: Especificar mediante constante el numero de entidades/enemigos

    auto& colComps = gc.getCollisionComponents();
   
    for(auto& notification : notifications) {

        if (!notification.en.heal) continue;
        //if ( notification.en.lod  &&  !notification.en.lod->activeBehaviour ) continue;
        if(notification.en.sens->timeToUpdatePerception >= notification.en.sens->kTimeRangeUpdatePerception){
            notification.en.sens->timeToUpdatePerception = 0;
            //Check if there is a object between player and enemy
            notification.rSense.vision.boxRootInf.collided = false;
            for(auto& col : colComps){
                auto* ent = gc.getEntityById(col.getEntityID());
                if(!ent->sens){
                    colsys.checkBetween(notification.rSense.vision.boxRootSup,
                    col.boxRoot, notification.posEn + notification.rSense.vision.positionRelative,
                    gc.getPositionComponentByID(col.getEntityID())->position,notification.pos);
                    colsys.checkBetween(notification.rSense.vision.boxRootInf,
                    col.boxRoot, notification.posEn + notification.rSense.vision.positionRelative,
                    gc.getPositionComponentByID(col.getEntityID())->position,notification.pos);
                } 
            }

            if(((!notification.rSense.vision.boxRootSup.collided) &&(colsys.checkObjectCollision(notification.rSense.vision.boxRootSup,
            notification.body, notification.posEn + notification.rSense.vision.positionRelative,
            notification.pos))) || ((!notification.rSense.vision.boxRootInf.collided) && 
            colsys.checkObjectCollision(notification.rSense.vision.boxRootInf,
            notification.body, notification.posEn + notification.rSense.vision.positionRelative,
            notification.pos))){
                sensoryMemory.updateVision(gc.getEntityById(notification.en.id));
            }
            else{
                if(notification.noise.box.vertex1.x != 0 || !notification.en.sens->clueless){
                    if(colsys.checkObjectCollision(notification.rSense.hearing,
                    notification.noise,notification.posEn,notification.pos)){
                        sensoryMemory.updateSound(gc.getEntityById(notification.en.id));
                    }
                }else if(glm::distance(notification.posEn,notification.pos) == 0) {
                    sensoryMemory.updateSound(gc.getEntityById(notification.en.id));
                }
            }
                 
        }
        else{
            notification.en.sens->timeToUpdatePerception += dt;
       }    
       if(!sensoryMemory.isWithinFOV(gc.getEntityById(notification.en.id)) || sensoryMemory.isSensed(gc.getEntityById(notification.en.id))){
            sensoryMemory.checkToForget(gc.getEntityById(notification.en.id), dt);
            notification.en.ai->currentPointMapID = gc.getMapComponent().getClosestKeyPoint(notification.en.pos->position);
        }

        sensoryMemory.check2React(notification.en,colsys);
        enemies.push_back(gc.getEntityById(notification.en.id));
    }
    

    arbiter.blackboardIteration(enemies);
}






