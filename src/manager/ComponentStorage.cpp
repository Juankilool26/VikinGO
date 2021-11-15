#include "ComponentStorage.hpp"
#include <algorithm>

#define kNumCameras 1


namespace ARCS {


ComponentStorage::ComponentStorage(std::size_t initialize)
{
    physicsComponents.reserve(initialize);
    renderComponents.reserve(initialize);
    inputComponents.reserve(initialize);
    collisionComponents.reserve(initialize);
    cameraComponents.reserve(kNumCameras);
    healthComponents.reserve(initialize);
    positionComponents.reserve(initialize);
    sensorialPerceptionComponents.reserve(initialize);
    behaviourComponents.reserve(initialize);
    weaponComponents.reserve(initialize);
    aiComponents.reserve(initialize);
    visualDepurationComponents.reserve(initialize);
    lodComponents.reserve(initialize);
    schedulingComponents.reserve(initialize);
    arrowComponents.reserve(initialize);
}


PhysicsComponent& ComponentStorage::createPhysicsComponent(int entID){
    return physicsComponents.emplace_back(entID);
}

PositionComponent& ComponentStorage::createPositionComponent(int entID){
    return positionComponents.emplace_back(entID);
}

RenderComponent& ComponentStorage::createRenderComponent(int entID){
    return renderComponents.emplace_back(entID);
}

InputComponent& ComponentStorage::createInputComponent(int entID){
    return inputComponents.emplace_back(entID);
}

CollisionComponent& ComponentStorage::createCollisionComponent(int entID){
    return collisionComponents.emplace_back(entID);
}

HealthComponent& ComponentStorage::createHealthComponent(int entID){
    return healthComponents.emplace_back(entID);
}

CameraComponent& ComponentStorage::createCameraComponent(int entID){
    return cameraComponents.emplace_back(entID);
}

AIComponent& ComponentStorage::createAIComponent(int entID){
    return aiComponents.emplace_back(entID);
}

SensorialPerceptionComponent& ComponentStorage::createSensorialPerceptionComponent(int entID){
    return sensorialPerceptionComponents.emplace_back(entID);
}

BehaviourComponent& ComponentStorage::createBehaviourComponent(int entID){
    return behaviourComponents.emplace_back(entID);
}

WeaponComponent& ComponentStorage::createWeaponComponent(int entID){
    return weaponComponents.emplace_back(entID);
}

VisualDepurationComponent& ComponentStorage::createVisualDepurationComponent(int entID){
    return visualDepurationComponents.emplace_back(entID);
}

LoDComponent& ComponentStorage::createLoDComponent(int entID){
    return lodComponents.emplace_back(entID);
}

SchedulingComponent& ComponentStorage::createSchedulingComponent(int entID){
    return schedulingComponents.emplace_back(entID);
}

ArrowComponent& ComponentStorage::createArrowComponent(int entID){
    return arrowComponents.emplace_back(entID);
}



RenderComponent* ComponentStorage::deleteRenderComponentByEntityID(int eid) {

    auto it =
        std::find_if(renderComponents.begin(), renderComponents.end(),
            [&eid](RenderComponent& rend) { return rend.getEntityID() == eid; }
        );
    if ( it == renderComponents.end() ) return 0;

    if ( it + 1  !=  renderComponents.end() )
        *it = renderComponents.back();
    renderComponents.pop_back();

    return it.base();
}



PhysicsComponent* ComponentStorage::deletePhysicsComponentByEntityID(int eid) {

    auto it =
        std::find_if(physicsComponents.begin(), physicsComponents.end(),
            [&eid](PhysicsComponent& phy) { return phy.getEntityID() == eid; }
        );
    if ( it == physicsComponents.end() ) return 0;

    if ( it + 1  !=  physicsComponents.end() )
        *it = physicsComponents.back();
    physicsComponents.pop_back();

    return it.base();
}



InputComponent* ComponentStorage::deleteInputComponentByEntityID(int eid) {

    auto it =
        std::find_if(inputComponents.begin(), inputComponents.end(),
            [&eid](InputComponent& inp) { return inp.getEntityID() == eid; }
        );
    if ( it == inputComponents.end() ) return 0;

    if ( it + 1  !=  inputComponents.end() )
        *it = inputComponents.back();
    inputComponents.pop_back();

    return it.base();
}



HealthComponent* ComponentStorage::deleteHealthComponentByEntityID(int eid) {

    auto it =
        std::find_if(healthComponents.begin(), healthComponents.end(),
            [&eid](HealthComponent& heal) { return heal.getEntityID() == eid; }
        );
    if ( it == healthComponents.end() ) return 0;

    if ( it + 1  !=  healthComponents.end() )
        *it = healthComponents.back();
    healthComponents.pop_back();

    return it.base();
}



CollisionComponent* ComponentStorage::deleteCollisionComponentByEntityID(int eid) {

    auto it =
        std::find_if(collisionComponents.begin(), collisionComponents.end(),
            [&eid](CollisionComponent& col) { return col.getEntityID() == eid; }
        );
    if ( it == collisionComponents.end() ) return 0;

    if ( it + 1  !=  collisionComponents.end() )
        *it = collisionComponents.back();
    collisionComponents.pop_back();

    return it.base();
}



CameraComponent* ComponentStorage::deleteCameraComponentByEntityID(int eid) {

    auto it =
        std::find_if(cameraComponents.begin(), cameraComponents.end(),
            [&eid](CameraComponent& cam) { return cam.getEntityID() == eid; }
        );
    if ( it == cameraComponents.end() ) return 0;

    if ( it + 1  !=  cameraComponents.end() )
        *it = cameraComponents.back();
    cameraComponents.pop_back();

    return it.base();
}



PositionComponent* ComponentStorage::deletePositionComponentByEntityID(int eid) {

    auto it =
        std::find_if(positionComponents.begin(), positionComponents.end(),
            [&eid](PositionComponent& pos) { return pos.getEntityID() == eid; }
        );
    if ( it == positionComponents.end() ) return 0;

    if ( it + 1  !=  positionComponents.end() )
        *it = positionComponents.back();
    positionComponents.pop_back();

    return it.base();
}



AIComponent* ComponentStorage::deleteAIComponentByEntityID(int eid) {

    auto it =
        std::find_if(aiComponents.begin(), aiComponents.end(),
            [&eid](AIComponent& ai) { return ai.getEntityID() == eid; }
        );
    if ( it == aiComponents.end() ) return 0;

    if ( it + 1  !=  aiComponents.end() )
        *it = aiComponents.back();
    aiComponents.pop_back();

    return it.base();
}



SensorialPerceptionComponent* ComponentStorage::deleteSensorialPerceptionComponentByEntityID(int eid) {

    auto it =
        std::find_if(sensorialPerceptionComponents.begin(), sensorialPerceptionComponents.end(),
            [&eid](SensorialPerceptionComponent& sens) { return sens.getEntityID() == eid; }
        );
    if ( it == sensorialPerceptionComponents.end() ) return 0;

    if ( it + 1  !=  sensorialPerceptionComponents.end() )
        *it = sensorialPerceptionComponents.back();
    sensorialPerceptionComponents.pop_back();

    return it.base();
}




/*
BehaviourComponent* ComponentStorage::deleteBehaviourComponentByEntityID(int eid) {

    auto it =
        std::find_if(behaviourComponents.begin(), behaviourComponents.end(),
            [&eid](BehaviourComponent& bh) { return bh.getEntityID() == eid; }
        );
    if ( it == behaviourComponents.end() ) return 0;

    if ( it + 1  != behaviourComponents.end() )
        *it = behaviourComponents.back();
    behaviourComponents.pop_back();

    return it.base();
}
*/




WeaponComponent* ComponentStorage::deleteWeaponComponentByEntityID(int eid) {

    auto it =
        std::find_if(weaponComponents.begin(), weaponComponents.end(),
            [&eid](WeaponComponent& wp) { return wp.getEntityID() == eid; }
        );
    if ( it == weaponComponents.end() ) return 0;

    if ( it + 1  != weaponComponents.end() )
        *it = weaponComponents.back();
    weaponComponents.pop_back();

    return it.base();
}




VisualDepurationComponent* ComponentStorage::deleteVisualDepurationComponentByEntityID(int eid) {

    auto it =
        std::find_if(visualDepurationComponents.begin(), visualDepurationComponents.end(),
            [&eid](VisualDepurationComponent& vd) { return vd.getEntityID() == eid; }
        );
    if ( it == visualDepurationComponents.end() ) return 0;

    if ( it + 1  != visualDepurationComponents.end() )
        *it = visualDepurationComponents.back();
    visualDepurationComponents.pop_back();

    return it.base();
}




LoDComponent* ComponentStorage::deleteLoDComponentByEntityID(int eid) {

    auto it =
        std::find_if(lodComponents.begin(), lodComponents.end(),
            [&eid](LoDComponent& lod) { return lod.getEntityID() == eid; }
        );
    if ( it == lodComponents.end() ) return 0;

    if ( it + 1  != lodComponents.end() )
        *it = lodComponents.back();
    lodComponents.pop_back();

    return it.base();
}



ArrowComponent* ComponentStorage::deleteArrowComponentByEntityID(int eid) {

    auto it =
        std::find_if(arrowComponents.begin(), arrowComponents.end(),
            [&eid](ArrowComponent& arr) { return arr.getEntityID() == eid; }
        );
    if ( it == arrowComponents.end() ) return 0;

    if ( it + 1  != arrowComponents.end() )
        *it = arrowComponents.back();
    arrowComponents.pop_back();

    return it.base();
}




const MapComponent&
ComponentStorage::getMapComponent() const {
    return std::get<MapComponent>(singletonComponents);
}




MapComponent&
ComponentStorage::getMapComponent() {
    return std::get<MapComponent>(singletonComponents);
}





} // namespace ARCS