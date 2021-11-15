#pragma once

#include <facade/Devices/LeviatanStorage.hpp>
#include "FacadePhysics.hpp"


class FacadeLVPhysics: public FacadePhysics
{

public:
    explicit FacadeLVPhysics() = default;
    ~FacadeLVPhysics() = default;
    bool update(ARCS::PositionComponent &) override;
    void setMeshPosition(const int,const glm::vec3 &) override;
    void setMeshRotation(const int,const glm::vec3 &) override;
    void createEnemiesPatrol() override;
    void startCollisionPlayerMap(ARCS::Entity& ) override;
    void startCollisionCamMap() override;
    void initSelector(ARCS::Entity& ) override;
    void dropSelector() override;
    void addChild(const int ,const int ) override;


private:
    LeviatanStorage leviatan;
};
