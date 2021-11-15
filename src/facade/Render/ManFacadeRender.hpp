#pragma once

#include "FacadeRender.hpp"


class ManFacadeRender {
    
public:
    ~ManFacadeRender();
    FacadeRender* getFacade() { return facade; }
    static ManFacadeRender* GetInstance();

private:
    ManFacadeRender();
    FacadeRender* facade { 0 };
    inline static ManFacadeRender* m_Instance { 0 };

};
