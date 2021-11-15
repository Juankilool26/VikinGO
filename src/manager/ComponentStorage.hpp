#pragma once

#include <tuple>
#include <components/Physics.hpp>
#include <components/Render.hpp>
#include <components/Input.hpp>
#include <components/Collision.hpp>
#include <components/Health.hpp>
#include <components/Camera.hpp>
#include <components/AI.hpp>
#include <components/Position.hpp>
#include <components/SensorialPerception.hpp>
#include <components/Behaviour.hpp>
#include <components/Weapon.hpp>
#include <components/VisualDepuration.hpp>
#include <components/LoD.hpp>
#include <components/Map.hpp>
#include <components/Scheduling.hpp>
#include <components/Arrow.hpp>



namespace ARCS {




struct ComponentStorage {
      
      // No se puede crear por defecto
      ComponentStorage() = delete;
      explicit ComponentStorage(std::size_t initialize);

      // Destroy the copy and asignation components 
      ComponentStorage(const ComponentStorage&) = delete;
      ComponentStorage(ComponentStorage&&) = delete;
      ComponentStorage& operator=(const ComponentStorage&) = delete;
      ComponentStorage& operator=(ComponentStorage&&) = delete;

      PhysicsComponent&             createPhysicsComponent                       (int );
      RenderComponent&              createRenderComponent                        (int );
      InputComponent&               createInputComponent                         (int );
      CollisionComponent&           createCollisionComponent                     (int );
      HealthComponent&              createHealthComponent                        (int );
      CameraComponent&              createCameraComponent                        (int );
      PositionComponent&            createPositionComponent                      (int );
      AIComponent&                  createAIComponent                            (int );
      SensorialPerceptionComponent& createSensorialPerceptionComponent           (int );
      BehaviourComponent&           createBehaviourComponent                     (int );
      WeaponComponent&              createWeaponComponent                        (int );
      VisualDepurationComponent&    createVisualDepurationComponent              (int );
      LoDComponent&                 createLoDComponent                           (int );
      SchedulingComponent&          createSchedulingComponent                    (int );
      ArrowComponent&               createArrowComponent                         (int );

      RenderComponent*              deleteRenderComponentByEntityID              (int );
      PhysicsComponent*             deletePhysicsComponentByEntityID             (int );
      InputComponent*               deleteInputComponentByEntityID               (int );
      HealthComponent*              deleteHealthComponentByEntityID              (int );
      CollisionComponent*           deleteCollisionComponentByEntityID           (int );
      CameraComponent*              deleteCameraComponentByEntityID              (int );
      AIComponent*                  deleteAIComponentByEntityID                  (int );
      PositionComponent*            deletePositionComponentByEntityID            (int );
      SensorialPerceptionComponent* deleteSensorialPerceptionComponentByEntityID (int );
      WeaponComponent*              deleteWeaponComponentByEntityID              (int );
      VisualDepurationComponent*    deleteVisualDepurationComponentByEntityID    (int );
      LoDComponent*                 deleteLoDComponentByEntityID                 (int );
      ArrowComponent*               deleteArrowComponentByEntityID               (int );
      //SchedulingComponent*          deleteSchedulingComponentByEntityID          (int );
      //BehaviourComponent*  deleteBehaviourComponentByEntityID(int );

      const std::vector<PhysicsComponent>&   getPhysicsComponents()   const { return physicsComponents; }
            std::vector<PhysicsComponent>&   getPhysicsComponents()         { return physicsComponents; }

      const std::vector<RenderComponent>&    getRenderComponents()    const { return renderComponents; }
            std::vector<RenderComponent>&    getRenderComponents()          { return renderComponents; }

      const std::vector<InputComponent>&     getInputComponents()     const { return inputComponents; }
            std::vector<InputComponent>&     getInputComponents()           { return inputComponents; }

      const std::vector<CollisionComponent>& getCollisionComponents() const { return collisionComponents; }
            std::vector<CollisionComponent>& getCollisionComponents()       { return collisionComponents; }

      const std::vector<HealthComponent>&    getHealthComponents()    const { return healthComponents; }
            std::vector<HealthComponent>&    getHealthComponents()          { return healthComponents; }

      const std::vector<CameraComponent>&    getCameraComponents()    const { return cameraComponents; }
            std::vector<CameraComponent>&    getCameraComponents()          { return cameraComponents; }

      const std::vector<PositionComponent>&  getPositionComponents()  const { return positionComponents; }
            std::vector<PositionComponent>&  getPositionComponents()        { return positionComponents; }

      const std::vector<AIComponent>&  getAIComponents()  const { return aiComponents; }
            std::vector<AIComponent>&  getAIComponents()        { return aiComponents; }

      const std::vector<SensorialPerceptionComponent>&  getSensorialPerceptionComponents()  const { return sensorialPerceptionComponents; }
            std::vector<SensorialPerceptionComponent>&  getSensorialPerceptionComponents()        { return sensorialPerceptionComponents; }

      const std::vector<BehaviourComponent>&  getBehaviourComponents()  const { return behaviourComponents; }
            std::vector<BehaviourComponent>&  getBehaviourComponents()        { return behaviourComponents; }

      const std::vector<WeaponComponent>&  getWeaponComponents()  const { return weaponComponents; }
            std::vector<WeaponComponent>&  getWeaponComponents()        { return weaponComponents; }

      const std::vector<VisualDepurationComponent>&  getVisualDepurationComponents()  const { return visualDepurationComponents; }
            std::vector<VisualDepurationComponent>&  getVisualDepurationComponents()        { return visualDepurationComponents; }

      const std::vector<LoDComponent>&  getLoDComponents()  const { return lodComponents; }
            std::vector<LoDComponent>&  getLoDComponents()        { return lodComponents; }
      
      const std::vector<SchedulingComponent>&  getSchedulingComponents()  const { return schedulingComponents; }
            std::vector<SchedulingComponent>&  getSchedulingComponents()        { return schedulingComponents; }

      const std::vector<ArrowComponent>&  getArrowComponents()  const { return arrowComponents; }
            std::vector<ArrowComponent>&  getArrowComponents()        { return arrowComponents; }

      const MapComponent&  getMapComponent() const;
            MapComponent&  getMapComponent();



private:
      std::vector<PhysicsComponent>             physicsComponents             { };
      std::vector<RenderComponent>              renderComponents              { };
      std::vector<InputComponent>               inputComponents               { };
      std::vector<CollisionComponent>           collisionComponents           { };
      std::vector<HealthComponent>              healthComponents              { };
      std::vector<CameraComponent>              cameraComponents              { };
      std::vector<PositionComponent>            positionComponents            { };
      std::vector<AIComponent>                  aiComponents                  { };
      std::vector<SensorialPerceptionComponent> sensorialPerceptionComponents { };
      std::vector<BehaviourComponent>           behaviourComponents           { };
      std::vector<WeaponComponent>              weaponComponents              { };
      std::vector<VisualDepurationComponent>    visualDepurationComponents    { };
      std::vector<LoDComponent>                 lodComponents                 { };
      std::vector<SchedulingComponent>          schedulingComponents          { };
      std::vector<ArrowComponent>               arrowComponents               { };
      std::tuple<MapComponent>                  singletonComponents           { };

};




} // namespace ARCS