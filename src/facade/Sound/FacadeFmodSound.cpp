#include <facade/Sound/FacadeFmodSound.hpp>
#include <glm/glm.hpp>


FacadeFmodSound::FacadeFmodSound()
    : totalSounds { static_cast<std::size_t>(KeySound::TOTAL_SOUNDS) }
{
    events.reserve(totalSounds);
    paramDesc.reserve(totalSounds);
    eventInstances.reserve(totalSounds);
    //Common_Init(&extraDriverData);
    ERRCHECK(FMOD::Studio::System::create(&system));
    ERRCHECK(system->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, extraDriverData));
    ERRCHECK(system->loadBankFile("media/sounds/Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank));
    ERRCHECK(system->loadBankFile("media/sounds/Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank));
}


FacadeFmodSound::~FacadeFmodSound(){
    ERRCHECK(masterBank->unload());
    ERRCHECK(stringsBank->unload());
    for (unsigned int i=0; i<totalSounds; ++i)
        if (eventInstances[i])
            ERRCHECK(eventInstances[i]->release());
    ERRCHECK(system->release());
}

void FacadeFmodSound::update(){
    //Common_Update();
    ERRCHECK(system->update());
}

void FacadeFmodSound::instanceEvent(std::string_view eventName, std::string_view parameter){
    int n = eventName.length();
    ERRCHECK(system->getEvent(eventName.data(), &events[instancesCount]));
    n = parameter.length();
    if (n>0){
        ERRCHECK(events[instancesCount]->getParameterDescriptionByName(parameter.data(), &paramDesc[instancesCount]));
    }
    ERRCHECK(events[instancesCount]->createInstance(&eventInstances[instancesCount]));
    //if (n > 0)
    ERRCHECK(eventInstances[instancesCount]->setParameterByID(paramDesc[instancesCount].id, surfaceParameter));

    ++instancesCount;
}

void FacadeFmodSound::startEvent(KeySound key){
    auto id { static_cast<unsigned int>(key) };
    ERRCHECK(eventInstances[id]->start());
}

void FacadeFmodSound::stopEvent(KeySound key){
    auto id { static_cast<unsigned int>(key) };
    ERRCHECK(eventInstances[id]->stop(FMOD_STUDIO_STOP_IMMEDIATE));
}


void FacadeFmodSound::stopAllEvents() {
    for (unsigned int i=0; i<eventInstances.size(); ++i)
        ERRCHECK(eventInstances[i]->stop(FMOD_STUDIO_STOP_IMMEDIATE));
}


void FacadeFmodSound::releaseEvent(KeySound key) {
    auto id { static_cast<unsigned int>(key) };

    ERRCHECK(eventInstances[id]->release());
    //if ( events[id] != nullptr )
    //    events[id] = nullptr;
    //auto desc { paramDesc.begin() };
    //paramDesc.erase(desc);
    --instancesCount;
}

void FacadeFmodSound::set3DAttributes(KeySound key, const glm::vec3& pos, const glm::vec3& pos2, const glm::vec3& rot){
    auto id { static_cast<unsigned int>(key) };

    FMOD_VECTOR vec;
    vec.x = 0.5 * pos.x;
    vec.y = 0.5 * pos.y;
    vec.z = 0.5 * pos.z;

    FMOD_3D_ATTRIBUTES a;
    a.position = vec;
    a.forward = {1.0, 0.0, 0.0};
    a.up = {0.0, 1.0, 0.0};
    //atr.velocity = {vel*0.1f, vel*0.1f, vel*0.1f};
    ERRCHECK(eventInstances[id]->set3DAttributes(&a));

    FMOD_VECTOR vec2;
    vec2.x = 0.5 * pos2.x;
    vec2.y = 0.5 * pos2.y;
    vec2.z = 0.5 * pos2.z;

    FMOD_3D_ATTRIBUTES a2;
    a2.position = {vec2};
    a2.forward = {-glm::cos(glm::radians(rot.y)), 0.0, glm::sin(glm::radians(rot.y))};
    a2.up = {0.0, 1.0, 0.0};
    //atr.velocity = {0.0, 0.0, 0.0};
    
    ERRCHECK(system->setListenerAttributes(0,&a2));

}

void FacadeFmodSound::changeParameter(float f, KeySound key) {
    auto id { static_cast<unsigned int>(key) };
    ERRCHECK(eventInstances[id]->setParameterByID(paramDesc[id].id, f));
}



void FacadeFmodSound::ERRCHECK_fn(unsigned int result, const char *file, int line) {
    if (result != FMOD_OK) {
        //std::cerr << file << "(" << line << "): FMOD error " << result << " - " << FMOD_ErrorString(result) << std::endl;
        //exit(-1);         // FIXED: JC esto se puede comentar????
    }
}