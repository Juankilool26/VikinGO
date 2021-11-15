#pragma once

#include <string_view>
#include <cstring>
#include <glm/vec3.hpp>
#include <util/KeySounds.hpp>


struct FacadeSound {
    virtual ~FacadeSound() = default;
    virtual void update() = 0;
    virtual void instanceEvent(std::string_view, std::string_view) = 0;
    virtual void startEvent(KeySound ) = 0;
    virtual void stopEvent(KeySound ) = 0;
    virtual void stopAllEvents() = 0;
    virtual void releaseEvent(KeySound ) = 0;
    virtual void changeParameter(float f,KeySound key) = 0;
    virtual void set3DAttributes(KeySound key,const glm::vec3& pos,const glm::vec3& pos2,const glm::vec3& rot) = 0;
    virtual void ERRCHECK_fn(unsigned int result, const char *file, int line) = 0;
};