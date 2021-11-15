#pragma once

#include <facade/Devices/IrrlichtStorage.hpp>
#include "FacadePhysics.hpp"


using namespace irr;


//#define DISTANCE_FRONT_OF_PLAYER	30.f
//#define ENEMY_PATROL_GLANCE			1.5f
//#define PI 			 				3.14159f
//#define WEAPON_ATTACK_SPEED			90.f
//#define ADITIONAL_SPEED_ALERT		35.f
//#define WEAPON_ATTACK_WAITING		1.5f
//#define ATTACK_RANGE				20.f
//#define PLAYER_ATTACK_RANGE			26.f
//#define ENEMY_LIFES	                4


class FacadeIrrPhysics: public FacadePhysics
{

public:
    explicit FacadeIrrPhysics() = default;
    bool update(ARCS::PositionComponent &) override;
    void setMeshPosition(const int,const glm::vec3 &) override;
    void setMeshRotation(const int,const glm::vec3 &) override;
    void addChild(const int ,const int ) override;
    
    void createEnemiesPatrol() override;
    void startCollisionPlayerMap(ARCS::Entity& ) override;
    void startCollisionCamMap() override;
    void initSelector(ARCS::Entity& ) override;
    void dropSelector() override;


private:
    IrrlichtStorage irrlicht { };

    //ISceneNodeAnimator* anim { NULL };
    //std::vector<ISceneNodeAnimatorCollisionResponse*> animators { };
    //ITriangleSelector* selector = 0;
    //std::vector<std::vector<core::vector3df>> pointPatrol { };
    //std::vector<bool> alert { }, hiting { };
    //std::vector<f32> waiting { }, waitingAttack { };
    //std::vector<core::vector3df> attackMaxDistance { }, attackMaxMovement { };
    //std::vector<int> next;
    //std::vector<bool> quiet;
};
