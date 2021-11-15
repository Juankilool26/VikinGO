#pragma once

#include "FacadeSound.hpp"


class ManFacadeSound{
    
    public: 
    ~ManFacadeSound();
    FacadeSound* getFacade(){return facade;}
    static ManFacadeSound* GetInstance();

    private:
    ManFacadeSound();
    FacadeSound* facade =  { 0 }; 
    inline static ManFacadeSound* m_Instance { 0 };

};
