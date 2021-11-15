#pragma once

#include <LevelOfDetailAI/BehaviorRecord.hpp>


namespace LOD {


struct GoToNextPointPatrol : BehaviorRecord {
    bool isValid(MemoryRecord&,ARCS::ArrowComponent&,ARCS::PositionComponent&,ARCS::AIComponent&,ARCS::WeaponComponent&,MapComponent&) override;
    void enter(MemoryRecord&,ARCS::ArrowComponent&,ARCS::PositionComponent&,ARCS::AIComponent&,ARCS::WeaponComponent&,MapComponent&)   override;
    void exit(MemoryRecord&,ARCS::ArrowComponent&,ARCS::PositionComponent&,ARCS::AIComponent&,ARCS::WeaponComponent&,MapComponent&)    override;
};


} // namespace LOD