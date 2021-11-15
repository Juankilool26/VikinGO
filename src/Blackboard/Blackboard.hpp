#pragma once

#include <glm/vec3.hpp>
#include <vector>
#include <facade/Render/ManFacadeRender.hpp>
#include <components/Entity.hpp>

struct Blackboard{
    public:
        inline static int maxTimesDiscovered { 5 };

        ~Blackboard(); 
        static Blackboard* GetInstance();
        glm::vec3& getPlayerPosition(){ return playerPos; }   
        bool getDetected(){ return detected; }
        bool getViewed() { return viewed; }
        void setPlayerPosition(glm::vec3 pos){ playerPos = pos; }
        void setDetected(){ detected = true; }
        void setViewed(){  viewed = true; }
        //void setExpert(ARCS::Entity* e) { expertsListActions.push_back(e); }
        void setUndetected(){ detected = false; }
        void setUnviewed(){ viewed = false; }
        void setTime(float t){ timeBecameDetected = t; }
        void oneDiscovers(){ discovered++; ManFacadeRender::GetInstance()->getFacade()->drawStealthBar(discovered);};
        void restartDiscoveredTimes(){ discovered = 0; };
        int getTimesDiscovered(){ return discovered; };
        float& getTime(){ return timeBecameDetected; }
        void run();
        

    private:
        Blackboard();
        inline static Blackboard* blackboard_instance { 0 };   
        glm::vec3 playerPos;
        float timeBecameDetected;
        bool detected;
        bool viewed;
        int discovered { 0 };
        //std::vector<ARCS::Entity*> expertsListActions;
};