#include "TriggerSystem.hpp"
#include <facade/Render/ManFacadeRender.hpp>



TriggerSystem::TriggerSystem(){
    m_triggers.reserve(10);                        // FIXED: Especificar una variable para los triggers que hbran en el juego o nivel
}




TriggerSystem::~TriggerSystem(){
    Clear();
}



void
TriggerSystem::Clear(){
    m_triggers.clear();
}




bool
TriggerSystem::update(ARCS::GameContext& gc, ARCS::CollisionSystem& cs, float delta){
    ManFacadeRender::GetInstance()->getFacade()->interClean(); 
    UpdateTriggers(delta);
    return TryTriggers(gc, cs, delta);
}




Trigger&
TriggerSystem::Register(Trigger* t){
    m_triggers.push_back(t);
    return *t;
}




void
TriggerSystem::UpdateTriggers(float delta)
{
    TriggerList::iterator currentTrigger = m_triggers.begin();
    while (currentTrigger != m_triggers.end()){

        //remove if is dead
        if((*currentTrigger)->isToBeRemoved()){
            currentTrigger = m_triggers.erase(currentTrigger);
            currentTrigger = m_triggers.end();
        }
        else{

            //update the trigger
            (*currentTrigger)->Update(delta);
            currentTrigger++;
        }
        
    }
}




bool
TriggerSystem::TryTriggers(ARCS::GameContext& gc, ARCS::CollisionSystem& cs, float delta)
{
    TriggerList::const_iterator curTrg;
    for (curTrg = m_triggers.begin(); curTrg != m_triggers.end(); ++curTrg)
    {
        if( (*curTrg)->Try(gc, cs, delta) )
            return true;
    }
    return false;
}

