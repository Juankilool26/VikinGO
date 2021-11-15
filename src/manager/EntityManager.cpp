#include <algorithm>
#include <facade/Render/ManFacadeRender.hpp>
#include "EntityManager.hpp"



namespace ARCS {



EntityManager::EntityManager(){
    entities.reserve(kNumEntities);
}



const Entity* 
EntityManager::getEntityById(int entID) const {
    auto it = std::find_if(entities.begin(), entities.end(),
        [&entID](const Entity& e) { return e.id == entID; } );

    if(it == entities.end())
        return 0;

    return it.base();
}



Entity*
EntityManager::getEntityById(int entID) {
    auto eptr = const_cast<const EntityManager*>(this)->getEntityById(entID);

    return const_cast<Entity*>(eptr);
}




const Entity&
EntityManager::getPlayer() const {
    return *getEntityById( getInputComponents()[0].getEntityID() );
}




Entity&
EntityManager::getPlayer() {
    auto& player { const_cast<const EntityManager*>(this)->getPlayer() };

    return const_cast<Entity&>(player);
}





void
EntityManager::destroyEntityById(int eid) {
    auto* entity { getEntityById(eid) };
    if (!entity) return;

    if ( entity->phy ) {
        auto* phyptr = components.deletePhysicsComponentByEntityID(eid);
        if (!phyptr) goto update_AI_ptr;
        auto* entityMoved = getEntityById( phyptr->getEntityID() );
        entityMoved->phy = phyptr;
    }
update_AI_ptr:
    if ( entity->ai ) {
        auto* aiptr = components.deleteAIComponentByEntityID(eid);
        if (!aiptr) goto update_collide_ptr;
        auto* entityMoved = getEntityById( aiptr->getEntityID() );
        entityMoved->ai = aiptr;
    }
update_collide_ptr:
    if ( entity->col ) {
        auto* colptr = components.deleteCollisionComponentByEntityID(eid);
        if (!colptr) goto update_LoD_ptr;
        auto* entityMoved = getEntityById( colptr->getEntityID() );
        entityMoved->col = colptr;
    }
update_LoD_ptr:
    if ( entity->lod ) {
        auto* lodptr = components.deleteLoDComponentByEntityID(eid);
        if (!lodptr) goto update_Arrow_ptr;
        auto* entityMoved = getEntityById( lodptr->getEntityID() );
        entityMoved->lod = lodptr;
    }                                                                           // TODO: Delete Scheduling Component
update_Arrow_ptr:
    if ( entity->arr ) {
        auto* arrptr = components.deleteArrowComponentByEntityID(eid);
        if (!arrptr) goto update_Sensory_ptr;
        auto* entityMoved = getEntityById( arrptr->getEntityID() );
        entityMoved->arr = arrptr;
    }
update_Sensory_ptr:
    if ( entity->sens ) {
        auto* sensptr = components.deleteSensorialPerceptionComponentByEntityID(eid);
        if (!sensptr) goto update_Visual_ptr;
        auto* entityMoved = getEntityById( sensptr->getEntityID() );
        entityMoved->sens = sensptr;
    }
update_Visual_ptr:
    if ( entity->vd ) {
        for (auto& vis : entity->vd->visualID)
            ManFacadeRender::GetInstance()->getFacade()->setVisible(vis, false);
        auto* vdptr = components.deleteVisualDepurationComponentByEntityID(eid);
        if (!vdptr) goto update_Health_ptr;
        auto* entityMoved = getEntityById( vdptr->getEntityID() );
        entityMoved->vd = vdptr;
    }
update_Health_ptr:
    if ( entity->heal ) {
        ManFacadeRender::GetInstance()->getFacade()->setVisible(eid + 5000, false);
        ManFacadeRender::GetInstance()->getFacade()->setVisible(eid + 6000, false);
    }
    
}








const PhysicsComponent*
EntityManager::getPhysicsComponentByID(int eid) const {
    const Entity* entity { getEntityById(eid) };

    return entity->phy;
}





PhysicsComponent*
EntityManager::getPhysicsComponentByID(int eid) {
    auto phyptr = const_cast<const EntityManager *>(this)->getPhysicsComponentByID(eid);

    return const_cast<PhysicsComponent *>(phyptr);
}




const CollisionComponent*
EntityManager::getCollisionComponentByID(int eid) const {
    const Entity* entity { getEntityById(eid) };
    
    return entity->col;
}





CollisionComponent*
EntityManager::getCollisionComponentByID(int eid) {
    auto colptr = const_cast<const EntityManager *>(this)->getCollisionComponentByID(eid);

    return const_cast<CollisionComponent *>(colptr);
}






const PositionComponent*
EntityManager::getPositionComponentByID(int eid) const {
    const Entity* entity { getEntityById(eid) };

    return entity->pos;
}





PositionComponent*
EntityManager::getPositionComponentByID(int eid) {
    auto posptr = const_cast<const EntityManager *>(this)->getPositionComponentByID(eid);

    return const_cast<PositionComponent *>(posptr);
}






const CameraComponent*
EntityManager::getCameraComponentByID(int eid) const {
    const Entity* entity { getEntityById(eid) };

    return entity->cam;
}





CameraComponent*
EntityManager::getCameraComponentByID(int eid) {
    auto camptr = const_cast<const EntityManager*>(this)->getCameraComponentByID(eid);

    return const_cast<CameraComponent *>(camptr);
}






const SensorialPerceptionComponent*
EntityManager::getSensorialPerceptionComponentByID(int eid) const {
    const Entity* entity { getEntityById(eid) };

    return entity->sens;
}




SensorialPerceptionComponent*
EntityManager::getSensorialPerceptionComponentByID(int eid) {
    auto posptr = const_cast<const EntityManager *>(this)->getSensorialPerceptionComponentByID(eid);

    return const_cast<SensorialPerceptionComponent *>(posptr);
}




const WeaponComponent*
EntityManager::getWeaponComponentByID(int eid) const {
    const Entity* entity { getEntityById(eid) };

    return entity->wc;
}





WeaponComponent*
EntityManager::getWeaponComponentByID(int eid) {
    auto wcptr = const_cast<const EntityManager*>(this)->getWeaponComponentByID(eid);

    return const_cast<WeaponComponent *>(wcptr);
}




const LoDComponent*
EntityManager::getLoDComponentByID(int eid) const {
    const Entity* entity { getEntityById(eid) };

    return entity->lod;
}





LoDComponent*
EntityManager::getLoDComponentByID(int eid) {
    auto lodptr = const_cast<const EntityManager*>(this)->getLoDComponentByID(eid);

    return const_cast<LoDComponent *>(lodptr);
}




const AIComponent*
EntityManager::getAIComponentByID(int eid) const {
    const Entity* entity { getEntityById(eid) };

    return entity->ai;
}





AIComponent*
EntityManager::getAIComponentByID(int eid) {
    auto aiptr = const_cast<const EntityManager*>(this)->getAIComponentByID(eid);

    return const_cast<AIComponent *>(aiptr);
}





Entity&
EntityManager::createEntity(){
    return entities.emplace_back();
}



RenderComponent&
EntityManager::addRenderComponent(Entity& e) {
    return components.createRenderComponent( e.id );
}



PositionComponent&
EntityManager::addPositionComponent(Entity& e) {
    return components.createPositionComponent( e.id );
}



PhysicsComponent&
EntityManager::addPhysicsComponent(Entity& e) {
    return components.createPhysicsComponent( e.id );
}



InputComponent&
EntityManager::addInputComponent(Entity& e) {
    return components.createInputComponent( e.id );
}



CollisionComponent&
EntityManager::addCollisionComponent(Entity& e) {
    return components.createCollisionComponent( e.id );
}



HealthComponent&
EntityManager::addHealthComponent(Entity& e) {
    return components.createHealthComponent( e.id );
}



CameraComponent&
EntityManager::addCameraComponent(Entity& e) {
    return components.createCameraComponent( e.id );
}


AIComponent&
EntityManager::addAIComponent(Entity& e) {
    return components.createAIComponent( e.id );
}



SensorialPerceptionComponent&
EntityManager::addSensorialPerceptionComponent(Entity& e) {
    return components.createSensorialPerceptionComponent( e.id );
}



BehaviourComponent&
EntityManager::addBehaviourComponent(Entity& e) {
    return components.createBehaviourComponent( e.id );
}



WeaponComponent&
EntityManager::addWeaponComponent(Entity& e) {
    return components.createWeaponComponent( e.id );
}




VisualDepurationComponent&
EntityManager::addVisualDepurationComponent(Entity& e) {
    return components.createVisualDepurationComponent( e.id );
}



LoDComponent&
EntityManager::addLoDComponent(Entity& e) {
    return components.createLoDComponent( e.id );
}



SchedulingComponent&
EntityManager::addSchedulingComponent(Entity& e) {
    return components.createSchedulingComponent( e.id );
}



ArrowComponent&
EntityManager::addArrowComponent(Entity& e) {
    return components.createArrowComponent( e.id );
}




} // namespace ARCS