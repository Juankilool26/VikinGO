#pragma once

#include <components/Component.hpp>
#include <SensorialPerception/Notification.hpp>

namespace ARCS {

struct SensorialPerceptionComponent : public Component {

    explicit SensorialPerceptionComponent(int entID)
        : Component(entID){
    };

    RegionalSense rSense;
    bool clueless { true };
    inline static constexpr float kMinDistance2Face { 3.5f };
    float timeToUpdatePerception = 0;
    float kTimeRangeUpdatePerception = 1.0;

  
};
    
} // namespace ARCS