#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <facade/Devices/IrrEventReceiver.hpp>


using namespace irr;


#define kScreenWidth  1280
#define kScreenHeight 720


class IrrlichtStorage {

public:

    // Build Irrlicht
    explicit IrrlichtStorage();
    ~IrrlichtStorage();
    static const core::vector3df glm3fcore(const glm::vec3 &);
    static const glm::vec3 core3fglm(const core::vector3df );
    static const glm::vec2 core2iglm(const core::vector2di );

    // Irrlitch Graphic Engine
    inline static irr::IrrlichtDevice* device { 0 };
    inline static video::IVideoDriver* driver { 0 };
    inline static scene::ISceneManager* smgr { 0 };
    inline static gui::IGUIEnvironment* guienv { 0 };
    inline static IrrEventReceiver receiver { };
};