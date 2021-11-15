#pragma once

#include "Key.hpp"
#include "Orb.hpp"
#include "Lever.hpp"
#include "Trap.hpp"
#include "ConversationNPC.hpp"
#include "HealthRecover.hpp"
#include "ActivatorTrigger.hpp"
#include "DangerAdvisor.hpp"
#include "TriggerSystem.hpp"


struct TriggerStorage
{

    explicit TriggerStorage();
    Trigger& RegisterKey(ARCS::Entity &ent,TriggerSystem& ts, int);
    Trigger& RegisterOrb(ARCS::Entity &ent,TriggerSystem& ts);
    Trigger& RegisterTrap(ARCS::Entity &ent,TriggerSystem& ts);
    Trigger& RegisterLever(ARCS::Entity &ent, TriggerSystem& ts);
    Trigger& RegisterConversation(ARCS::Entity &ent,TriggerSystem& ts,KeySound ,int );
    Trigger& RegisterBeer(ARCS::Entity &ent,TriggerSystem& ts);
    Trigger& RegisterActivator(ARCS::Entity &ent,TriggerSystem& ts, Trigger&);
    Trigger& RegisterAdvisor(ARCS::Entity &ent,TriggerSystem& ts,KeySound );

private:
    std::vector<Key>                keys;
    std::vector<Orb>                orbs;
    std::vector<Lever>              levers;
    std::vector<Trap>               traps;
    std::vector<ConversationNPC>    convers;
    std::vector<HealthRecover>      beers;
    std::vector<ActivatorTrigger>   activators;
    std::vector<DangerAdvisor>      dAdvisors;

};


