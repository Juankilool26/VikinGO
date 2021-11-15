#pragma once

#include <LevelOfDetailAI/BehaviorRecord.hpp>


namespace LOD {



struct DodgeObstacle : BehaviorRecord {
    bool isValid(MemoryRecord&,ARCS::ArrowComponent&,ARCS::PositionComponent&,ARCS::AIComponent&,ARCS::WeaponComponent&,MapComponent&) override;
    void enter(MemoryRecord&,ARCS::ArrowComponent&,ARCS::PositionComponent&,ARCS::AIComponent&,ARCS::WeaponComponent&,MapComponent&)   override;
    void exit(MemoryRecord&,ARCS::ArrowComponent&,ARCS::PositionComponent&,ARCS::AIComponent&,ARCS::WeaponComponent&,MapComponent&)    override;
};



} // namespace LOD