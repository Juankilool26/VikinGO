#include <facade/Input/FacadeIrrInput.hpp>




bool
FacadeIrrInput::isKeyPressed(int key) const {
    if (irrlicht.receiver.IsKeyDown(static_cast<irr::EKEY_CODE>(key)))
        return true;
    else
        return false;
}

bool
FacadeIrrInput::isMouseLeftDown() const {
    return irrlicht.receiver.IsLeftMouseDown();
}




glm::vec2
FacadeIrrInput::getMousePosition() const {
    //return irrlicht.core2iglm( irrlicht.receiver.getScreenMousePosition() );
    return irrlicht.core2iglm( irrlicht.device->getCursorControl()->getPosition() );
}



void
FacadeIrrInput::setMousePosition(unsigned int x, unsigned int y) {
    irrlicht.device->getCursorControl()->setPosition(core::position2di(x, y));
}