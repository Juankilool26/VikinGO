#pragma once

#include <components/Component.hpp>
#include <glm/vec3.hpp>


namespace ARCS {

struct ArrowComponent : public Component
{
    explicit ArrowComponent(int );

    static float gravity;
    static float floorHeight;

    int arrowID { 0 };
    bool active { false };
    float velocity { 0.0f };
    glm::vec3 angle { 0, 0, 0 };
    float accumulatedTime { 0.0f };
    float flightTime { 0.0f };
    glm::vec3 displacement { 0, 0, 0 };
};

} // namespace ARCS