#pragma once

#include <components/Component.hpp>
#include <array>
#include <string_view>
#include <glm/vec3.hpp>


namespace ARCS {


struct VisualDepurationComponent : public Component
{

    explicit VisualDepurationComponent(int );

    inline static constexpr int kNumMaxObj { 4 };


    using ArrayID  = std::array<int, kNumMaxObj>;
    using ArrayObj = std::array<std::string_view, kNumMaxObj>;
    using ArrayPos = std::array<glm::vec3, kNumMaxObj>;

    ArrayID visualID;
    static ArrayPos visualPos;
    static ArrayObj visualObj;
};


} // namespace ARCS