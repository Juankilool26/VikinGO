#include "FrequencyScheduler.hpp"



namespace SCH {



void
FrequencyScheduler::run(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map) noexcept {
    ++currentFrame;
    for (auto& behavior : behaviors)
        if ( currentFrame % behavior->frequency  ==  behavior->phase )
            behavior->node->run(mr, arr, pos, ai, wp, map);
}


void
FrequencyScheduler::addBehavior(UPNode node, unsigned int frecuency, unsigned int phase) {
    auto newBehavior = std::make_unique<BehaviorRecord>(std::move(node), frecuency, phase);
    behaviors.push_back( std::move(newBehavior) );
}



} // namespace SCH