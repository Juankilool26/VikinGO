#pragma once

#include <vector>
#include <components/Entity.hpp>
#include <components/SensorialPerception.hpp>
#include <components/Behaviour.hpp>
#include <components/Map.hpp>



namespace ARCS {



struct GameContext {
    virtual ~GameContext() = default;

    virtual const Entity* getEntityById(int) const = 0;
    virtual       Entity* getEntityById(int)       = 0;

    virtual void destroyEntityById(int) = 0;

    virtual const std::vector<Entity>& getEntities() const = 0;
    virtual       std::vector<Entity>& getEntities()       = 0;

    virtual const Entity& getPlayer() const = 0;
    virtual       Entity& getPlayer()       = 0;


    virtual const std::vector<PhysicsComponent>& getPhysicsComponents() const = 0;
    virtual       std::vector<PhysicsComponent>& getPhysicsComponents()       = 0;

    virtual const std::vector<RenderComponent>& getRenderComponents() const = 0;
    virtual       std::vector<RenderComponent>& getRenderComponents()       = 0;

    virtual const std::vector<InputComponent>& getInputComponents() const = 0;
    virtual       std::vector<InputComponent>& getInputComponents()       = 0;

    virtual const std::vector<CollisionComponent>& getCollisionComponents() const = 0;
    virtual       std::vector<CollisionComponent>& getCollisionComponents()       = 0;

    virtual const std::vector<HealthComponent>& getHealthComponents() const = 0; 
    virtual       std::vector<HealthComponent>& getHealthComponents()       = 0;

    virtual const std::vector<CameraComponent>& getCameraComponents() const = 0; 
    virtual       std::vector<CameraComponent>& getCameraComponents()       = 0;

    virtual const std::vector<PositionComponent>& getPositionComponents() const = 0; 
    virtual       std::vector<PositionComponent>& getPositionComponents()       = 0;
    
    virtual const std::vector<AIComponent>& getAIComponents() const = 0; 
    virtual       std::vector<AIComponent>& getAIComponents()       = 0;

    virtual const std::vector<SensorialPerceptionComponent>& getSensorialPerceptionComponents() const = 0; 
    virtual       std::vector<SensorialPerceptionComponent>& getSensorialPerceptionComponents()       = 0;

    virtual const std::vector<BehaviourComponent>& getBehaviourComponents() const = 0;
    virtual       std::vector<BehaviourComponent>& getBehaviourComponents()       = 0;

    virtual const std::vector<WeaponComponent>& getWeaponComponents() const = 0;
    virtual       std::vector<WeaponComponent>& getWeaponComponents()       = 0;

    virtual const std::vector<VisualDepurationComponent>& getVisualDepurationComponents() const = 0;
    virtual       std::vector<VisualDepurationComponent>& getVisualDepurationComponents()       = 0;

    virtual const std::vector<LoDComponent>& getLoDComponents() const = 0;
    virtual       std::vector<LoDComponent>& getLoDComponents()       = 0;

    virtual const std::vector<SchedulingComponent>& getSchedulingComponents() const = 0;
    virtual       std::vector<SchedulingComponent>& getSchedulingComponents()       = 0;

    virtual const std::vector<ArrowComponent>& getArrowComponents() const = 0;
    virtual       std::vector<ArrowComponent>& getArrowComponents()       = 0;

    virtual const MapComponent& getMapComponent() const = 0;
    virtual       MapComponent& getMapComponent()       = 0;


    virtual const SensorialPerceptionComponent* getSensorialPerceptionComponentByID(int ) const = 0;
    virtual       SensorialPerceptionComponent* getSensorialPerceptionComponentByID(int )       = 0;

    virtual const PhysicsComponent* getPhysicsComponentByID(int ) const = 0;
    virtual       PhysicsComponent* getPhysicsComponentByID(int )       = 0;

    virtual const CollisionComponent* getCollisionComponentByID(int ) const = 0;
    virtual       CollisionComponent* getCollisionComponentByID(int )       = 0;

    virtual const PositionComponent* getPositionComponentByID(int ) const = 0;
    virtual       PositionComponent* getPositionComponentByID(int )       = 0;

    virtual const CameraComponent* getCameraComponentByID(int ) const = 0;
    virtual       CameraComponent* getCameraComponentByID(int )       = 0;

    virtual const WeaponComponent* getWeaponComponentByID(int ) const = 0;
    virtual       WeaponComponent* getWeaponComponentByID(int )       = 0;

    virtual const LoDComponent* getLoDComponentByID(int ) const = 0;
    virtual       LoDComponent* getLoDComponentByID(int )       = 0;

    virtual const AIComponent* getAIComponentByID(int ) const = 0;
    virtual       AIComponent* getAIComponentByID(int )       = 0;
    
};

} // namespace ARCS