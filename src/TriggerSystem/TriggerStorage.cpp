#include "TriggerStorage.hpp"


TriggerStorage::TriggerStorage(){
    keys.reserve(10);
    levers.reserve(10);
    traps.reserve(30);
    convers.reserve(10);
    beers.reserve(10);
    orbs.reserve(10);
    activators.reserve(10);
    dAdvisors.reserve(10);
}

Trigger& TriggerStorage::RegisterKey(ARCS::Entity &ent,TriggerSystem& ts, int idKey){
    auto& key = keys.emplace_back(10,ent.id,ent.id+1, idKey);
    key.boxRootRangeTrigger.box = {glm::vec3{-1,-1,-1},{1,1,1}};
    return ts.Register(&key);
}

Trigger& TriggerStorage::RegisterOrb(ARCS::Entity &ent,TriggerSystem& ts){
    auto& orb = orbs.emplace_back(50,ent.id,ent.id+1);
    orb.boxRootRangeTrigger.box = {glm::vec3{-1,-1,-1},{1,1,1}};
    return ts.Register(&orb);
}
Trigger& TriggerStorage::RegisterTrap(ARCS::Entity &ent,TriggerSystem& ts){
    auto& trap = traps.emplace_back(50,ent.id);
    trap.boxRootRangeTrigger.box = {glm::vec3{-1,-2.5,-1},{1,2.5,1}};
    return ts.Register(&trap);
}
Trigger& TriggerStorage::RegisterLever(ARCS::Entity &ent, TriggerSystem& ts){
    auto& lever = levers.emplace_back(ent.id,ent.id+1);
    lever.boxRootRangeTrigger.box = {glm::vec3{-1,-1,-1},{1,1,1}};
    lever.boxRootRangeTrigger.box.vertex1 += glm::vec3(-2,-2,-2); // FIXED:: no debe ser un valor fijo
    lever.boxRootRangeTrigger.box.vertex2 += glm::vec3(2,2,2);
    return ts.Register(&lever);
}

Trigger& TriggerStorage::RegisterConversation(ARCS::Entity &ent,TriggerSystem& ts, KeySound sound, int idConv){
    auto& conv = convers.emplace_back(ent.id, sound, idConv);
    conv.boxRootRangeTrigger.box = {glm::vec3{-1,-1,-1},{1,1,1}};
    conv.boxRootRangeTrigger.box.vertex1 += glm::vec3(-1,-1,-1); // FIXED:: no debe ser un valor fijo
    conv.boxRootRangeTrigger.box.vertex2 += glm::vec3(1,1,1);
    return ts.Register(&conv);
}

Trigger& TriggerStorage::RegisterBeer(ARCS::Entity &ent,TriggerSystem& ts){
    auto& beer = beers.emplace_back(10,ent.id);
    beer.boxRootRangeTrigger.box = {glm::vec3{-1,-1,-1},{1,1,1}};
    return ts.Register(&beer);
}

Trigger& TriggerStorage::RegisterActivator(ARCS::Entity &ent,TriggerSystem& ts, Trigger& t){
    auto& act = activators.emplace_back(ent.id,t);
    act.boxRootRangeTrigger.box = {glm::vec3{-2,-2,-2},{2,2,2}};
    return ts.Register(&act);
}

Trigger& TriggerStorage::RegisterAdvisor(ARCS::Entity &ent,TriggerSystem& ts, KeySound s){
    auto& act = dAdvisors.emplace_back(ent.id, s);
    act.boxRootRangeTrigger.box = {glm::vec3{-2,-2,-2},{2,2,2}};
    return ts.Register(&act);
}
