#include <manager/GameContext.hpp>
#include <components/Map.hpp>
#include "BehaviourSystem.hpp"
#include "CollisionSystem.hpp"



namespace ARCS {




BehaviourSystem::BehaviourSystem(SensoryMemory& sm)
    : sMemory { sm }
{ }

unsigned int BehaviourSystem::getFarPointPatrol(GameContext &gc,std::vector<glm::vec3> pointsPatrol, int mapId) const{
    int dev = -1;
    int cont = 0;
    int maxDistance = 0;
    const auto& mapcmp { gc.getMapComponent() };
    auto currentMapPoint { mapcmp.getKeyPointByID(mapId) };
    for(auto pp : pointsPatrol){
        if(glm::distance(pp,currentMapPoint) > maxDistance){
            maxDistance = glm::distance(pp,currentMapPoint);
            dev = cont;
        }
        ++cont;
    }
    return dev;
}



bool
BehaviourSystem::update(GameContext &gc, CollisionSystem &colsys) const noexcept {
    auto& behaviours { gc.getBehaviourComponents() };  
    auto& mapcmp { gc.getMapComponent() };
    

    for(auto& bh : behaviours)
    {
        auto* ent = gc.getEntityById(bh.getEntityID());
        if (!ent) continue;

        // Apply behaviour Level of Detail
        if ( ent->lod  &&  !ent->lod->activeBehaviour ) continue;

        // Check objects as obstacles
        auto& memoryRecord { sMemory.getMemoryRecordFromMap(ent) };
        if (!memoryRecord.isMemoryEmpty() || !ent->ai->inPatrol) {
            checkObstacle(gc,colsys,*ent);
            ent->ai->actualPoint = getFarPointPatrol(gc, ent->ai->pointsPatrol, mapcmp.getClosestKeyPoint(ent->pos->position));
        }else{
            ent->ai->beetween = false;
        }

        // Run Behaviour Tree
        if( ent->phy  &&  ent->pos  &&  ent->wc )
            bh.bhTree.run(memoryRecord, *ent->arr, *ent->pos, *ent->ai, *ent->wc, mapcmp);
    }
    return true;
}


void
BehaviourSystem::checkObstacle(GameContext &gc, CollisionSystem &colsys, Entity &ent) const{
    auto* player {gc.getEntityById(gc.getInputComponents()[0].getEntityID())};
    auto& colComps{ gc.getCollisionComponents() };

    ent.ai->actualPoint = getFarPointPatrol(gc,ent.ai->pointsPatrol,ent.ai->currentPointMapID);
    ent.ai->beetween = false;

    BoundingBoxNode aux;
    aux.box.vertex1 = glm::vec3(-0.6,-1,-0.6);
    aux.box.vertex2 = glm::vec3(0.6,1,0.6);
    for(auto& col : colComps){
        auto* obstacle = gc.getEntityById(col.getEntityID());
        if(!obstacle->sens){
            colsys.checkBetween(aux,
            col.boxRoot, ent.pos->position + glm::vec3(0.5 * ent.phy->speedDisplacementVector.x,0,0.5 * ent.phy->speedDisplacementVector.z),
            gc.getPositionComponentByID(col.getEntityID())->position,player->pos->position);
            ent.ai->beetween = aux.collided;
        }
    }
}

}
 // namespace ARCS

