#pragma once

#include <components/Component.hpp>
#include <glm/vec2.hpp>



namespace ARCS {

struct InputComponent : public Component {
    explicit InputComponent(int entID) 
        : Component { entID }
    { };


   /*  inline static constexpr glm::vec2 kPercentageMouseSpeed { 0.1f, 0.05f };
    inline static constexpr float kLimitDurationRun {1.8};
    inline static constexpr float kTimeRecoverStamina {4.0}; 
    float stamina {1.8};*/

    static glm::vec2 kPercentageMouseSpeed;
    inline static constexpr float kLimitDurationRun {3.5};
    inline static constexpr float kTimeRecoverStamina {7.0};
    float stamina {3.5};
    float recover {0.0};
};

} // namespace ARCS