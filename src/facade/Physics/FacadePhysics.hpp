#pragma once


#include <glm/vec3.hpp>


namespace ARCS {
    struct PositionComponent;
    struct Entity;
}



class FacadePhysics {

public:
    virtual ~FacadePhysics() = default;
    virtual bool update(ARCS::PositionComponent &) = 0;
    virtual void setMeshPosition(const int,const glm::vec3 &) = 0;
    virtual void setMeshRotation(const int,const glm::vec3 &) = 0;
    virtual void createEnemiesPatrol() = 0;
    virtual void startCollisionPlayerMap(ARCS::Entity& ) = 0;
    virtual void startCollisionCamMap() = 0;
    virtual void initSelector(ARCS::Entity& ) = 0;
    virtual void dropSelector() = 0;
    virtual void addChild(const int ,const int ) = 0;

};
