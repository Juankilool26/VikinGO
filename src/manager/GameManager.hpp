#pragma once

#include <chrono>
#include <Blackboard/Blackboard.hpp>
#include <facade/Sound/ManFacadeSound.hpp>
#include <manager/EntityManager.hpp>
#include <system/RenderSystem.hpp>
#include <system/PhysicsSystem.hpp>
#include <system/PositionSystem.hpp>
#include <system/InputSystem.hpp>
#include <system/CollisionSystem.hpp>
#include <system/HealthSystem.hpp>
#include <system/SensorialPerceptionSystem.hpp>
#include <system/CameraSystem.hpp>
#include <system/LoDSystem.hpp>
#include <system/BehaviourSystem.hpp>
#include <system/WeaponSystem.hpp>
#include <system/AISystem.hpp>
#include <system/VisualDepurationSystem.hpp>
#include <system/ArrowSystem.hpp>
#include <system/SchedulingSystem.hpp>
#include <TriggerSystem/TriggerStorage.hpp>
#include <RecordMemory/SensoryMemory.hpp>
#include <Blackboard/Arbiter.hpp>
#include <util/KeyCodes.hpp>
#include <util/GameObjectFactory.hpp>
#include <manager/StateManager.hpp>
#include <manager/PauseMenu.hpp>





namespace ARCS {




struct Level : StateBase {

    explicit Level(ARCS::StateManager& sm, int& l, std::string_view s, ARCS::RenderSystem& rs, bool);
    ~Level();
    void update(float deltaTime) final;
    bool alive() final;

private:
    // Managers
    ARCS::EntityManager entity_man { };
    GameObjectFactory GOFact { entity_man };
    TriggerStorage trigger_sto{ };
    ARCS::StateManager& SM;
    int& lvl;
    ARCS::Entity& player;
    bool playing = true;
    glm::vec3 finalPos;
    float timeReturnPause = 0.5;

    // Systems
    ARCS::RenderSystem &render_sys;
    ARCS::PhysicsSystem physics_sys { };
    ARCS::PositionSystem position_sys { };
    ARCS::InputSystem input_sys { };
    ARCS::CollisionSystem collision_sys { };
    ARCS::CameraSystem camera_sys { };
    ARCS::HealthSystem health_sys { collision_sys }; 		// TODO: Add system after doing collision system or others
    ARCS::WeaponSystem weapon_sys { };
    ARCS::VisualDepurationSystem depuration_sys { };

    ARCS::AISystem ai_sys { };
    ARCS::LoDSystem lod_sys { };
    TriggerSystem trigger_sys{ }; 

    //AI
    SensoryMemory sensoryMemory{player, 5.0};
    Arbiter arbiter{sensoryMemory};
    SensorialPerceptionSystem sensorial_sys { collision_sys, entity_man, sensoryMemory, arbiter };
    ARCS::BehaviourSystem behaviour_sys { sensoryMemory };
    ARCS::ArrowSystem arrow_sys { };
    ARCS::SchedulingSystem schedul_sys { sensoryMemory };
};





struct GameManager : StateBase {

    explicit GameManager(ARCS::StateManager& sm, ARCS::RenderSystem& rs);
    ~GameManager();
    void update(float deltaTime) final;
    bool alive() final;
    void nextLevel();

private:
    ARCS::StateManager& SM;
    ARCS::RenderSystem &render_sys;
        
    bool playing = true;
    int level = 0;
    int lastlevel = -1;
};



} // namespace ARCS