#pragma once

#include <glm/vec2.hpp>



namespace ARCS {


struct GameContext;

class PhysicsSystem {
    
public:
    explicit PhysicsSystem() = default;
    bool update(GameContext& gc, float dt) const;

};


} // namespace ARCS