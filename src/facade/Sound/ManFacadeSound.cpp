#include "ManFacadeSound.hpp"
#include "FacadeFmodSound.hpp"


ManFacadeSound::ManFacadeSound(){
    facade = new FacadeFmodSound();
}

ManFacadeSound::~ManFacadeSound(){
    delete facade;
    facade = 0;
}

ManFacadeSound* ManFacadeSound::GetInstance() {
    if (!m_Instance)
        m_Instance = new ManFacadeSound();
    return m_Instance;
}
