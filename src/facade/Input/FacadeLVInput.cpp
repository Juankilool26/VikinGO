#include "FacadeLVInput.hpp"


bool FacadeLVInput::isKeyPressed(int key) const
{
    return leviatan.device->processInput(leviatan.device->getWindow(), key);
}
bool FacadeLVInput::isMouseLeftDown() const
{
    return leviatan.device->mouseIsDown(leviatan.device->getWindow());
}
glm::vec2 FacadeLVInput::getMousePosition() const
{
    return leviatan.device->getCursorPosition();
}
void FacadeLVInput::setMousePosition(unsigned int x, unsigned int y )
{
    leviatan.device->setCursorPosition(x,y);
}