#pragma once

#include <manager/GameContext.hpp>
#include <manager/ComponentStorage.hpp>


namespace ARCS {


class EntityManager : public GameContext {

public:
      static constexpr std::size_t kNumEntities   { 4000 };
      static constexpr std::size_t kNumComponents { 4000 };

      explicit EntityManager();
      
      Entity& createEntity();

      RenderComponent&              addRenderComponent              (Entity& e);
      PhysicsComponent&             addPhysicsComponent             (Entity& e);
      InputComponent&               addInputComponent               (Entity& e);
      CollisionComponent&           addCollisionComponent           (Entity& e);
      CameraComponent&              addCameraComponent              (Entity& e);
      HealthComponent&              addHealthComponent              (Entity& e);
      PositionComponent&            addPositionComponent            (Entity& e);
      AIComponent&                  addAIComponent                  (Entity& e);
      SensorialPerceptionComponent& addSensorialPerceptionComponent (Entity& e);
      BehaviourComponent&           addBehaviourComponent           (Entity& e);
      WeaponComponent&              addWeaponComponent              (Entity& e);
      VisualDepurationComponent&    addVisualDepurationComponent    (Entity& e);
      LoDComponent&                 addLoDComponent                 (Entity& e);
      SchedulingComponent&          addSchedulingComponent          (Entity& e);
      ArrowComponent&               addArrowComponent               (Entity& e);

      const Entity* getEntityById(int) const override;
            Entity* getEntityById(int)       override;

      void destroyEntityById(int ) override;

      const std::vector<Entity>& getEntities() const override { return entities; } 
            std::vector<Entity>& getEntities()       override { return entities; }
      
      const Entity& getPlayer() const override;
            Entity& getPlayer()       override;
            

      const std::vector<PhysicsComponent>& getPhysicsComponents() const override { return components.getPhysicsComponents(); }
            std::vector<PhysicsComponent>& getPhysicsComponents()       override { return components.getPhysicsComponents(); }

      const std::vector<RenderComponent>& getRenderComponents() const override { return components.getRenderComponents(); }
            std::vector<RenderComponent>& getRenderComponents()       override { return components.getRenderComponents(); }

      const std::vector<InputComponent>& getInputComponents() const override { return components.getInputComponents(); }
            std::vector<InputComponent>& getInputComponents()       override { return components.getInputComponents(); }

      const std::vector<CollisionComponent>& getCollisionComponents() const override { return components.getCollisionComponents(); }
            std::vector<CollisionComponent>& getCollisionComponents()       override { return components.getCollisionComponents(); }
      
      const std::vector<HealthComponent>& getHealthComponents() const override { return components.getHealthComponents(); }
            std::vector<HealthComponent>& getHealthComponents()       override { return components.getHealthComponents(); }

      const std::vector<CameraComponent>& getCameraComponents() const override { return components.getCameraComponents(); }
            std::vector<CameraComponent>& getCameraComponents()       override { return components.getCameraComponents(); }

      const std::vector<PositionComponent>& getPositionComponents() const override { return components.getPositionComponents(); }
            std::vector<PositionComponent>& getPositionComponents()       override { return components.getPositionComponents(); }

      const std::vector<AIComponent>& getAIComponents() const override { return components.getAIComponents(); }
            std::vector<AIComponent>& getAIComponents()       override { return components.getAIComponents(); }

      const std::vector<SensorialPerceptionComponent>& getSensorialPerceptionComponents() const override { return components.getSensorialPerceptionComponents(); }
            std::vector<SensorialPerceptionComponent>& getSensorialPerceptionComponents()       override { return components.getSensorialPerceptionComponents(); }

      const std::vector<BehaviourComponent>& getBehaviourComponents() const override { return components.getBehaviourComponents(); }
            std::vector<BehaviourComponent>& getBehaviourComponents()       override { return components.getBehaviourComponents(); }

      const std::vector<WeaponComponent>& getWeaponComponents() const override { return components.getWeaponComponents(); }
            std::vector<WeaponComponent>& getWeaponComponents()       override { return components.getWeaponComponents(); }

      const std::vector<VisualDepurationComponent>& getVisualDepurationComponents() const override { return components.getVisualDepurationComponents(); }
            std::vector<VisualDepurationComponent>& getVisualDepurationComponents()       override { return components.getVisualDepurationComponents(); }

      const std::vector<LoDComponent>& getLoDComponents() const override { return components.getLoDComponents(); }
            std::vector<LoDComponent>& getLoDComponents()       override { return components.getLoDComponents(); }

      const std::vector<SchedulingComponent>& getSchedulingComponents() const override { return components.getSchedulingComponents(); }
            std::vector<SchedulingComponent>& getSchedulingComponents()       override { return components.getSchedulingComponents(); }

      const std::vector<ArrowComponent>& getArrowComponents() const override { return components.getArrowComponents(); }
            std::vector<ArrowComponent>& getArrowComponents()       override { return components.getArrowComponents(); }

      const MapComponent& getMapComponent() const override { return components.getMapComponent(); };
            MapComponent& getMapComponent()       override { return components.getMapComponent(); };
            

      const PhysicsComponent* getPhysicsComponentByID(int ) const override;
            PhysicsComponent* getPhysicsComponentByID(int )       override;

      const CollisionComponent* getCollisionComponentByID(int ) const override;
            CollisionComponent* getCollisionComponentByID(int )       override;

      const PositionComponent* getPositionComponentByID(int ) const override;
            PositionComponent* getPositionComponentByID(int )       override;

      const CameraComponent* getCameraComponentByID(int ) const override;
            CameraComponent* getCameraComponentByID(int )       override;

      const SensorialPerceptionComponent* getSensorialPerceptionComponentByID(int ) const override;
            SensorialPerceptionComponent* getSensorialPerceptionComponentByID(int )       override;

      const WeaponComponent* getWeaponComponentByID(int ) const override;
            WeaponComponent* getWeaponComponentByID(int )       override;

      const LoDComponent* getLoDComponentByID(int ) const override;
            LoDComponent* getLoDComponentByID(int )       override;

      const AIComponent* getAIComponentByID(int ) const override;
            AIComponent* getAIComponentByID(int )       override;

private:
      std::vector<Entity> entities { };
      ComponentStorage components { kNumComponents };

};

} //namespace ARCS  
