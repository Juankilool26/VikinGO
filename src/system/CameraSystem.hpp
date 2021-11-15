#pragma once

#include <facade/Render/ManFacadeRender.hpp>
#include <facade/Input/ManFacadeInput.hpp>


namespace ARCS {


struct GameContext;

class CameraSystem {
    
public:
    explicit CameraSystem();
    ~CameraSystem();
    bool update(GameContext &) const noexcept;

private:
    ManFacadeRender* manFacadeRender { 0 };

};


} // namespace ARCS