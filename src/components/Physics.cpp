#include "Physics.hpp"


namespace ARCS {



PhysicsComponent::PhysicsComponent(int entID)
    :   Component(entID)
{ }




bool
PhysicsComponent::isMovingAhead() const {
    return ( speedLinearVector.x == 1  &&  !speedLinearVector.z );
}




}