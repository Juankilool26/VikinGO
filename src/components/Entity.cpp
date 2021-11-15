#include "Entity.hpp"


namespace ARCS {


Entity::~Entity() {
    phy  = nullptr;
    rend = nullptr;
    inp  = nullptr;
    cam  = nullptr;
    heal = nullptr;
    col  = nullptr;
    pos  = nullptr;
    sens = nullptr;
    bh   = nullptr;
    wc   = nullptr;
    ai   = nullptr;
    vd   = nullptr;
    lod  = nullptr;
    sch  = nullptr;
    arr  = nullptr;
}



bool
Entity::isAlive() const {
    return ( heal  &&  heal->health > 0 );
}





void
Entity::restartCountID() {
    nextID = 0;
}


} // namespace