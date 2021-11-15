#pragma once

#include <vector>
#include <SensorialPerception/Notification.hpp>
#include <RecordMemory/SensoryMemory.hpp>
#include <Blackboard/Arbiter.hpp>

namespace ARCS{
    struct GameContext;
    struct CollisionSystem;
}

class SensorialPerceptionSystem{
    private:
        ARCS::CollisionSystem &colsys;
        std::vector<Notification> notifications;
        SensoryMemory &sensoryMemory;
        Arbiter &arbiter;
        

    public:
        explicit SensorialPerceptionSystem(ARCS::CollisionSystem &,ARCS::GameContext &,SensoryMemory &, Arbiter&);
        ~SensorialPerceptionSystem();
        void check(ARCS::GameContext&, float);
        bool update(ARCS::GameContext&, float);
        
        void destroyNotifications();
        

};