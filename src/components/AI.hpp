#pragma once

#include <glm/glm.hpp>
#include <components/Component.hpp>
#include <vector>



namespace ARCS {

inline static constexpr float PI { 3.14159265f };

struct AIComponent : public Component
{
    explicit AIComponent(int entID);

    glm::vec3 target { 0, 0, 0 };
    bool moving   { false };
    bool pointing { false };
    bool beetween { false };

    float perceptionTime  { 0.5f };
    float accumulatedTime { 0.0f };

    std::vector<glm::vec3> pointsPatrol { };
    unsigned int actualPoint = 0;
    bool inPatrol { true };
    unsigned int currentPointMapID = 0;

    inline static constexpr double kMaxAMov       { 0.03 };
    inline static constexpr float  kMinRange2Stop { 2.0f };
};

} // namespace ARCS