#pragma once

#include <facade/Input/ManFacadeInput.hpp>
#include <facade/Render/ManFacadeRender.hpp>
#include <util/KeyCodes.hpp>

namespace ARCS {

struct GameContext;

class InputSystem {

using clk = std::chrono::steady_clock;

public:
    explicit InputSystem();
    ~InputSystem();
    bool isKeyPressed(KeyCode );
    bool isMouseLeftDown() const;
    bool update(GameContext &,float);
    
private:
    ManFacadeInput*  manInputFacade  { nullptr };
    ManFacadeRender* manRenderFacade { nullptr };
};

} // namespace ARCS