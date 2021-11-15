#include <manager/GameContext.hpp>
#include "PositionSystem.hpp"


namespace ARCS {



PositionSystem::PositionSystem() {
    manPhysicsFacade = ManFacadePhysics::GetInstance();
}



PositionSystem::~PositionSystem() {
    //delete manPhysicsFacade;
    manPhysicsFacade = nullptr;
}



bool
PositionSystem::update(GameContext& gc) const noexcept {
    auto& posCmpVec { gc.getPositionComponents() };
    
    for (auto& poscmp : posCmpVec)
        manPhysicsFacade->getFacade()->update( poscmp );

    return true;
}



} // namespace ARCS