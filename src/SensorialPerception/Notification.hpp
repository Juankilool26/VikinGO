#pragma once

#include "RegionalSense.hpp"
#include <components/Position.hpp>

namespace ARCS{
    struct Entity;
}

struct Notification {
    ARCS::Entity &en; // Reference to enemy
    RegionalSense &rSense; //Enemy Senses
    ARCS::BoundingBoxNode &noise; // Player Noise
    ARCS::BoundingBoxNode &body; //Player body
    glm::vec3 &pos; //Player Pos
    glm::vec3 &posEn; //Enemy Pos

    Notification(ARCS::Entity &receiveEn, RegionalSense &receiveRsense, ARCS::BoundingBoxNode &receiveNoise,ARCS::BoundingBoxNode &receiveBody, glm::vec3 &receivePos, glm::vec3 &receivePosEn);
    ~Notification() = default;
};