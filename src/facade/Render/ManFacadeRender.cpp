#include "ManFacadeRender.hpp"
#include "FacadeLVRender.hpp"


ManFacadeRender::ManFacadeRender(){
    facade = new FacadeLVRender();
}

ManFacadeRender::~ManFacadeRender(){
    delete facade;
    facade = 0;
}

ManFacadeRender* ManFacadeRender::GetInstance() {
    if (!m_Instance)
        m_Instance = new ManFacadeRender();
    return m_Instance;
}
