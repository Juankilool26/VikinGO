#pragma once
#include <chrono>

namespace ARCS {


struct GameContext;

class WeaponSystem {

    using clk = std::chrono::steady_clock;
    
    public:
        explicit WeaponSystem() = default;
        ~WeaponSystem() = default;
        bool update(GameContext &,float ) const noexcept;

};



} // namespace ARCS