#pragma once

#include <facade/Physics/ManFacadePhysics.hpp>


namespace ARCS {


struct GameContext;

class PositionSystem {
    
public:
    explicit PositionSystem();
    ~PositionSystem();
    bool update(GameContext& gc) const noexcept;


private:
    ManFacadePhysics* manPhysicsFacade { 0 };

};


} // namespace ARCS