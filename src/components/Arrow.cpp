#include "Arrow.hpp"


namespace ARCS {

    

float ArrowComponent::gravity     { 9.8f };
float ArrowComponent::floorHeight { 0.2f };


ArrowComponent::ArrowComponent(int entID)
    : Component(entID)
{ }



}