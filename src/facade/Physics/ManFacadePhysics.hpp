#pragma once

#include "FacadePhysics.hpp"


class ManFacadePhysics {
    
public:
    ~ManFacadePhysics();
    FacadePhysics* getFacade() { return facade; }
    static ManFacadePhysics* GetInstance();

private:
    ManFacadePhysics();
    FacadePhysics* facade { 0 };
    inline static ManFacadePhysics* m_instance { 0 };
};
