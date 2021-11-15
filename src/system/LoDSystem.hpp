#pragma once


namespace ARCS {


struct GameContext;


struct LoDSystem {
    
    explicit LoDSystem() = default;
    ~LoDSystem() = default;
    bool update(GameContext &,float ) const noexcept;
};


} // namespace ARCS
