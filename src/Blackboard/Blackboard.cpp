#include "Blackboard.hpp"



Blackboard::Blackboard(){
    //expertsListActions.reserve(12);     // FIXED: Especificar variable tamanyo con expertos
}


Blackboard::~Blackboard(){
    //expertsListActions.clear();
    delete blackboard_instance;
    blackboard_instance = nullptr;
}


Blackboard* Blackboard::GetInstance() {
    if (!blackboard_instance)
        blackboard_instance = new Blackboard();
    return blackboard_instance;
}


void Blackboard::run(){
    //expertsListActions.clear();
}