#pragma once

#include <components/Component.hpp>
#include <glm/vec3.hpp>

namespace ARCS {

struct PhysicsComponent : public Component {

    explicit PhysicsComponent(int entID);
    bool isMovingAhead() const;


    glm::vec3 speedLinearVector  { 0, 0, 0 };
    glm::vec3 speedAngularVector { 0, 0, 0 };

    float speedLinear  { 0.0f };
    float sprintSpeed  { 0.0f };
    float normalSpeed  { 0.0f };
    float speedAngular { 0.0f };

    glm::vec3 speedDisplacementVector { 0, 0, 0 };
    float acceleration { 0.0f };
    inline static constexpr float accIncrement { 10.f };
};
    
} // namespace ARCS