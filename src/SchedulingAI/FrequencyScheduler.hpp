#pragma once

#include "BehaviorRecord.hpp"


namespace SCH {


struct FrequencyScheduler {
    using UPNode          = std::unique_ptr<Node>;
    using value_type      = std::unique_ptr<BehaviorRecord>;
    using BehaviorStorage = std::vector<value_type>;

    void run(MemoryRecord &,ARCS::ArrowComponent &,ARCS::PositionComponent &,ARCS::AIComponent &,ARCS::WeaponComponent &,MapComponent &) noexcept;
    void addBehavior(UPNode ,unsigned int ,unsigned int );

private:
    BehaviorStorage behaviors;
    unsigned long int currentFrame { 0 };
};



} // namespace SCH