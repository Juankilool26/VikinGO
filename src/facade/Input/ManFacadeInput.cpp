
#include "ManFacadeInput.hpp"
#include <facade/Input/FacadeLVInput.hpp>


ManFacadeInput::ManFacadeInput(){
    facade = new FacadeLVInput();
}

ManFacadeInput::~ManFacadeInput(){
    delete facade;
    facade = 0;
}

ManFacadeInput* ManFacadeInput::GetInstance() {
    if (!m_instance)
        m_instance = new ManFacadeInput();
    return m_instance;
}