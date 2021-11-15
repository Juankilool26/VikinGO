#pragma once

#include <components/Component.hpp>
#include <BehaviourTree/BehaviourTree/BehaviourTree.hpp>

namespace ARCS {

struct BehaviourComponent : public Component {

    explicit BehaviourComponent(int entID)
        : Component(entID)
    { };

    BehaviourTree bhTree { };
  
};
    
} // namespace ARCS