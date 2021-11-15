#pragma once

#include "Trigger.hpp" 
#include <manager/GameContext.hpp>
#include <vector>

class TriggerSystem {


public:
    typedef std::vector<Trigger*> TriggerList;

    TriggerSystem();
    ~TriggerSystem();
    void Clear();
    bool update(ARCS::GameContext& gc, ARCS::CollisionSystem& cs, float);
    Trigger& Register(Trigger* t);
    const TriggerList& getTriggers() const { return m_triggers; }

private:
    TriggerList m_triggers;
    void UpdateTriggers(float);
    bool TryTriggers(ARCS::GameContext& gc, ARCS::CollisionSystem& cs, float delta);

        
};