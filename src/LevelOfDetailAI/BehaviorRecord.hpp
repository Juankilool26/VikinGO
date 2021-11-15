#pragma once

#include <memory>
#include <BehaviourTree/BehaviourTree/Node.hpp>

namespace LOD {


struct BehaviorRecord {
    virtual ~BehaviorRecord() = default;

    virtual bool isValid(MemoryRecord&,ARCS::ArrowComponent&,ARCS::PositionComponent&,ARCS::AIComponent&,ARCS::WeaponComponent&,MapComponent&) = 0;
    virtual void enter(MemoryRecord&,ARCS::ArrowComponent&,ARCS::PositionComponent&,ARCS::AIComponent&,ARCS::WeaponComponent&,MapComponent&)   = 0;
    virtual void exit(MemoryRecord&,ARCS::ArrowComponent&,ARCS::PositionComponent&,ARCS::AIComponent&,ARCS::WeaponComponent&,MapComponent&)    = 0;

    std::unique_ptr<Node> behavior;
};


} // namespace LOD