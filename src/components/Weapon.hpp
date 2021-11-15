#pragma once

#include "Box.hpp"
#include <components/Component.hpp>
#include <chrono>


namespace ARCS {

struct WeaponComponent : public Component {

    using clk = std::chrono::steady_clock;

    explicit WeaponComponent(int entID)
        : Component(entID){
    };

    glm::vec3 wpositionRelative { };
    ARCS::BoundingBoxNode boxWeapon { };
    bool hiting { false };
    float displacement { limitTime4Waiting };
    float time2HitAgain { 0 };

    inline static constexpr float velocity  { 5.0f };
    inline static constexpr float limitDistance4Attacking { 2.5f };
    inline static constexpr float limitTime4Waiting { 1.0f };
};
    
} // namespace ARCS