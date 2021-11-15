#include "ManFacadePhysics.hpp"
#include "FacadeLVPhysics.hpp"


ManFacadePhysics::ManFacadePhysics(){
    facade = new FacadeLVPhysics();
}

ManFacadePhysics::~ManFacadePhysics(){
    delete facade;
    facade = 0;
}

ManFacadePhysics* ManFacadePhysics::GetInstance() {
    if (!m_instance)
        m_instance = new ManFacadePhysics();
    return m_instance;
}