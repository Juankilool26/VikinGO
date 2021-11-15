#include "Arbiter.hpp"
#include <cmath>


Arbiter::Arbiter(SensoryMemory &sm) : sensoryMemory{sm}{
    blackboard = Blackboard::GetInstance();
}

Arbiter::~Arbiter(){
    blackboard = nullptr;
    expert = nullptr;
}

void Arbiter::blackboardIteration(std::vector<ARCS::Entity*> experts){
    selectExpert(experts);  
    writeOnBlackboard();
    if (expert)
        readOnBlackboard(experts);
}

void Arbiter::selectExpert(std::vector<ARCS::Entity*> experts){
    int highInsistenceX = 1000;
    int highInsistenceZ = 1000;
    expert = 0;
    for (auto* ptrExp : experts){
        if(sensoryMemory.isSensed(ptrExp)){
            if(glm::abs(ptrExp->pos->position.x - sensoryMemory.getLastRecordedPositionOfOpponent(expert).x) < highInsistenceX && 
            glm::abs(ptrExp->pos->position.z - sensoryMemory.getLastRecordedPositionOfOpponent(expert).z) < highInsistenceZ){ //Maybe the insistence could be the alert state or the closeness with the player
                expert = ptrExp;
                highInsistenceX = glm::abs(ptrExp->pos->position.x - sensoryMemory.getLastRecordedPositionOfOpponent(expert).x);
                highInsistenceZ = glm::abs(ptrExp->pos->position.z - sensoryMemory.getLastRecordedPositionOfOpponent(expert).z);
            }
        }
    }
}

void Arbiter::writeOnBlackboard(){
    if(expert){ 
        ManFacadeRender::GetInstance()->getFacade()->drawSeen(true);
        blackboard->setDetected();
        blackboard->setTime(sensoryMemory.getTimeSinceLastSensed(expert));
        blackboard->setPlayerPosition(sensoryMemory.getLastRecordedPositionOfOpponent(expert));
       
        if(!sensoryMemory.isWithinFOV(expert) && !blackboard->getViewed()){ //enemigo visualiza al jugador y  lo escribe en la pizarra para que los demás sepan donde esta
            blackboard->setViewed();
        } 
    }
    else{
        blackboard->setUndetected();
        blackboard->setUnviewed();
        ManFacadeRender::GetInstance()->getFacade()->drawSeen(false);
    } 
}

void Arbiter::readOnBlackboard(std::vector<ARCS::Entity*> experts){
    if(blackboard->getDetected() || blackboard->getViewed()){
        for (auto* ptrExp : experts){
            if((glm::distance(ptrExp->pos->position, expert->pos->position) <= MAX_RANGE_ADVICE)){ //(expert->type == 3)){ //Si los enemigos estan cerca o el experto es el chivato se les dice cual es la posicion del player o donde fue escuchado
                sensoryMemory.setLastRecordedPositionOfOpponent(ptrExp,blackboard->getPlayerPosition(),blackboard->getTime());     
                // if(blackboard->getDetected()){
                //     if(blackboard->getViewed()){
                //         sensoryMemory.updateVision(ptrExp);
                //     }else{
                //         sensoryMemory.updateSound(ptrExp);
                //     }
                // }
            }
        }
    }
}
