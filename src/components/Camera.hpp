#pragma once

#include <glm/vec3.hpp>
#include <components/Component.hpp>

namespace ARCS {

    struct CameraComponent : public Component
    {
        explicit CameraComponent(int );
        float getRelativeDistance();
        void calculateRelativeDistance(const glm::vec3 &,const glm::vec3 &);

        int followEntityID { 0 };
        glm::vec3 lookat { 0, 0, 0 };
        glm::vec3 direction { 0, 0, 0 };
        bool crouched {false};
        static constexpr float distanceCrouchedDown { 1.2f }; //TODO: modificable
        inline static constexpr float kLimitTargetY { 1.5f };

    private:
        float distanceRelative { 0.0f };
    };
    
} // namespace ARCS