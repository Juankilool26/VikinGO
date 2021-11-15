#include "IrrlichtStorage.hpp"

IrrlichtStorage::IrrlichtStorage() {
    if (device) goto end_build_device;

    device = irr::createDevice(video::EDT_OPENGL, core::dimension2d<u32>(kScreenWidth, kScreenHeight), 16, false, false, false, &receiver);
    driver = device->getVideoDriver();
    smgr   = device->getSceneManager();
    guienv = device->getGUIEnvironment();

    // Set Cursor invisible
    device->getCursorControl()->setVisible(false);

end_build_device: ;
}

IrrlichtStorage::~IrrlichtStorage() {
    if (device) {
        device->drop();
        device = 0;
        driver = 0;
        smgr   = 0;
        guienv = 0;
    }
}

const core::vector3df
IrrlichtStorage::glm3fcore(const glm::vec3& vec) {
    return core::vector3df(vec.x, vec.y, vec.z);
}

const glm::vec3
IrrlichtStorage::core3fglm(const core::vector3df vec) {
    return glm::vec3(vec.X, vec.Y, vec.Z);
}

const glm::vec2
IrrlichtStorage::core2iglm(const core::vector2di vec) {
    return glm::vec2(static_cast<int>(vec.X), static_cast<int>(vec.Y));
}