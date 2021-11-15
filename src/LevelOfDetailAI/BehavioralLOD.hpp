#pragma once

#include <BehaviourTree/BehaviourTree/Node.hpp>
#include <vector>
#include <memory>
#include "BehaviorRecord.hpp"


namespace LOD {
    

struct BehavioralLOD : Node {
    ~BehavioralLOD();
    bool run(MemoryRecord&,ARCS::ArrowComponent&,ARCS::PositionComponent&,ARCS::AIComponent&,ARCS::WeaponComponent&,MapComponent&) override;


private:
    using UPRecord_t = std::unique_ptr<BehaviorRecord>;

    std::vector<UPRecord_t> records;
    BehaviorRecord* current { nullptr };
};



} // namespace LOD