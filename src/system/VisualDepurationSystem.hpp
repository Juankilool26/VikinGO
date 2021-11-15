#pragma once

#include <facade/Render/ManFacadeRender.hpp>
#include <facade/Input/ManFacadeInput.hpp>
#include <facade/Physics/ManFacadePhysics.hpp>


namespace ARCS {


struct GameContext;
struct VisualDepurationComponent;
struct WeaponComponent;
struct PositionComponent;


class VisualDepurationSystem {
    
public:
    explicit VisualDepurationSystem();
    ~VisualDepurationSystem();
    bool update(GameContext &,float ) noexcept;

private:
    void setVisualObjectsPosition(GameContext &,const VisualDepurationComponent &) noexcept;

    ManFacadeRender* manFacadeRender   { nullptr };
    ManFacadePhysics* manFacadePhysics { nullptr };
    ManFacadeInput*  manFacadeInput    { nullptr };
    bool activeMode { false };
    float time2Activate { 0.0f };
    inline static constexpr float kMaxTime2Activate { 1.0f };

};


} // namespace ARCS