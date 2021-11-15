#pragma once

#include <facade/Devices/IrrlichtStorage.hpp>
#include <facade/Input/FacadeInput.hpp>


class FacadeIrrInput: public FacadeInput
{

public:
    explicit FacadeIrrInput() = default;
    bool isKeyPressed(int ) const override;
    bool isMouseLeftDown() const override;
    glm::vec2 getMousePosition() const override;
    void setMousePosition(unsigned int, unsigned int ) override;
    
private:
    IrrlichtStorage irrlicht { };

};
