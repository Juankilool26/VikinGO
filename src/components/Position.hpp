#pragma once

#include <glm/vec3.hpp>
#include <components/Component.hpp>


namespace ARCS {


struct PositionComponent : public Component
{

    explicit PositionComponent(int entID)
        : Component ( entID )
    { };

    glm::vec3 position {0, 0, 0};
    glm::vec3 rotation {0, 0, 0};
};

    
} // namespace ARCS