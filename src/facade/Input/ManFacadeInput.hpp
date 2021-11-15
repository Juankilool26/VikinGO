#pragma once

#include "FacadeInput.hpp"


class ManFacadeInput {
    
public:
    ~ManFacadeInput();
    FacadeInput* getFacade() { return facade; }
    static ManFacadeInput* GetInstance();


private:
    ManFacadeInput();
    FacadeInput* facade { 0 };
    inline static ManFacadeInput* m_instance { 0 };

};
