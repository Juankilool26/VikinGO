#include "BehavioralLOD.hpp"



namespace LOD {



BehavioralLOD::~BehavioralLOD() {
    current = 0;
    records.clear();
}




bool
BehavioralLOD::run(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map) {
    BehaviorRecord* next { nullptr };

    // Check if we need to find a new behavior
    if ( current  &&  current->isValid(mr, arr, pos, ai, wp, map) )
        goto run_behavior_record_;

    // Find a new behavior, by checking each in turn
    for (auto& record : records)

        // Check if the record is valid
        if (record->isValid(mr, arr, pos, ai, wp, map)) {
            next = record.get();
            break;
        }
    
    // Update behaviors
    if ( current ) current->exit(mr, arr, pos, ai, wp, map);
    if ( next )    next->enter(mr, arr, pos, ai, wp, map);
    current = next;

run_behavior_record_:
    return current->behavior->run(mr, arr, pos, ai, wp, map);

}



} // namespace LOD