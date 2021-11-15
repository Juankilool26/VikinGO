#pragma once


namespace ARCS {


struct Component
{
    explicit Component(int eID) 
    : entityID { eID }
    {}

    const int getEntityID()    const;
    const int getComponentID() const;

private:
    inline static int nextID { 0 };
    int componentID { ++nextID };
    int entityID { 0 };
};


} // namespace ARCS