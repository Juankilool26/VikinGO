#pragma once



namespace ARCS {


struct GameContext;


class AISystem {
    
public:
    explicit AISystem() = default;
    bool update(GameContext& gc, float dt) const;

};


} // namespace ARCS