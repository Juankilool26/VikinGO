#pragma once

#include <memory>
#include <BehaviourTree/BehaviourTree/Node.hpp>


namespace SCH {


struct BehaviorRecord {
    using UPNode = std::unique_ptr<Node>;

    explicit BehaviorRecord(UPNode ,unsigned int ,unsigned int );

    UPNode node;
    unsigned int frequency { 0 };
    unsigned int phase { 0 };
};



} // namespace SCH