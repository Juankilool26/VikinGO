#pragma once

#include <RecordMemory/SensoryMemory.hpp>


namespace ARCS {


struct GameContext;


struct SchedulingSystem {
    
public:
    explicit SchedulingSystem(SensoryMemory &);
    bool update(GameContext& gc) const noexcept;

private:
    SensoryMemory& sMemory;

};


} // namespace ARCS