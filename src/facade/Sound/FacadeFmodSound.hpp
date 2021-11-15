#pragma once

#include <fmod/src/fmod_studio.hpp>
#include <fmod/src/fmod.hpp>
#include <fmod/src/fmod_errors.h>
#include <facade/Sound/FacadeSound.hpp>
#include <vector>




class FacadeFmodSound : public FacadeSound
{

public:
    explicit FacadeFmodSound();
    ~FacadeFmodSound();
    void update() override;
    void instanceEvent(std::string_view, std::string_view) override;
    void startEvent(KeySound ) override;
    void stopEvent(KeySound ) override;
    void stopAllEvents() override;
    void releaseEvent(KeySound ) override;
    void changeParameter(float f,KeySound key) override;
    void set3DAttributes(KeySound key,const glm::vec3& pos,const glm::vec3& pos2,const glm::vec3& rot) override;
    void ERRCHECK_fn(unsigned int result, const char *file, int line) override;


    #define ERRCHECK(_result) ERRCHECK_fn(_result, __FILE__, __LINE__)
    

private:
    void *extraDriverData = NULL;
    FMOD::Studio::System* system = NULL;
    FMOD::Studio::Bank* masterBank = NULL;
    FMOD::Studio::Bank* stringsBank = NULL;
    std::vector<FMOD::Studio::EventDescription*> events;
    std::vector<FMOD_STUDIO_PARAMETER_DESCRIPTION> paramDesc;
    float surfaceParameter { 0.0 };
    std::vector<FMOD::Studio::EventInstance*> eventInstances;
    int instancesCount { 0 };
    const unsigned int totalSounds { 0 };
};
