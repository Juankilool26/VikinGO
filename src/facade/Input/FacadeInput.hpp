#pragma once

#include <glm/vec2.hpp>


class FacadeInput {

public:
    virtual ~FacadeInput() = default;
    virtual bool isKeyPressed(int ) const = 0;
    virtual bool isMouseLeftDown() const = 0;
    virtual glm::vec2 getMousePosition() const = 0;
    virtual void setMousePosition(unsigned int, unsigned int ) = 0;

};