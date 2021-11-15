#pragma once

#include <components/Physics.hpp>
#include <components/Render.hpp>
#include <components/Input.hpp>
#include <components/Collision.hpp>
#include <components/Health.hpp>
#include <components/Camera.hpp>
#include <components/Position.hpp>
#include <components/AI.hpp>
#include <components/SensorialPerception.hpp>
#include <components/Behaviour.hpp>
#include <components/Weapon.hpp>
#include <components/VisualDepuration.hpp>
#include <components/LoD.hpp>
#include <components/Scheduling.hpp>
#include <components/Arrow.hpp>


namespace ARCS {

struct Entity {
    explicit Entity() = default;
    ~Entity();
    bool isAlive() const;

    PhysicsComponent*             phy  { nullptr };
    RenderComponent*              rend { nullptr };
    InputComponent*               inp  { nullptr };
    CollisionComponent*           col  { nullptr };
    HealthComponent*              heal { nullptr };
    CameraComponent*              cam  { nullptr };
    PositionComponent*            pos  { nullptr };
    AIComponent*                  ai   { nullptr };
    SensorialPerceptionComponent* sens { nullptr };
    BehaviourComponent*           bh   { nullptr };
    WeaponComponent*              wc   { nullptr };
    VisualDepurationComponent*    vd   { nullptr };
    LoDComponent*                 lod  { nullptr };
    SchedulingComponent*          sch  { nullptr };
    ArrowComponent*               arr  { nullptr };

    int id { ++nextID };

    static void restartCountID();
    
private:
    inline static int nextID { 0 };
};

} // namespace ARCS