#pragma once


#include "Blackboard.hpp"
#include <RecordMemory/SensoryMemory.hpp>

#define MAX_RANGE_ADVICE  20

class Arbiter{
    ARCS::Entity *expert;
    Blackboard *blackboard;
    SensoryMemory &sensoryMemory;

    public:
        Arbiter(SensoryMemory &);
        ~Arbiter();
        void blackboardIteration(std::vector<ARCS::Entity*>);
    private:
        void selectExpert(std::vector<ARCS::Entity*>);
        void writeOnBlackboard();
        void readOnBlackboard(std::vector<ARCS::Entity*>);

};