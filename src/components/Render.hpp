#pragma once

#include <components/Component.hpp>
#include <string_view>

namespace ARCS {

struct RenderComponent : public Component
{

    explicit RenderComponent(int entID)
        : Component ( entID )
    { };

    std::string_view object {""};
    bool animated {false};
    //glm::vec3 size {0, 0, 0};   // Width, Height, Depth
};
    
} // namespace ARCS