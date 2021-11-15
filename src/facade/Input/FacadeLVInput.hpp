#pragma once

#include <facade/Devices/LeviatanStorage.hpp>
#include "FacadeInput.hpp"


class FacadeLVInput: public FacadeInput
{

public:
    explicit FacadeLVInput() = default;
    bool isKeyPressed(int) const override;
    bool isMouseLeftDown() const override;
    glm::vec2 getMousePosition() const override;
    void setMousePosition(unsigned int, unsigned int ) override;
    
private:
    LeviatanStorage leviatan;

};
