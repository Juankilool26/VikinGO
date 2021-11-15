#pragma once
#include <components/Entity.hpp>
#include <system/CollisionSystem.hpp>
#include "MemoryRecord.hpp"
#include <map>



class SensoryMemory {
using clk = std::chrono::steady_clock;
    private:
        typedef std::map<ARCS::Entity*, MemoryRecord> memoryMap;            //para juntar la entidad con su memoria
        ARCS::Entity& player;
        memoryMap m_memoryMap;                                              //contenedor para simular memoria
        float memorySpan;  
        std::vector<ARCS::Entity> ent2React;
        void makeNewRecordIfNotAlreadyPresent(ARCS::Entity* entityPtr);
        bool isPlayerNear(ARCS::Entity &);
    
    public:
        SensoryMemory(ARCS::Entity& c_player, float c_memorySpan);
        ~SensoryMemory();

        void updateSound(ARCS::Entity *enemie);
        void updateVision(ARCS::Entity *enemie); 
        void checkToForget(ARCS::Entity* enemie, float);
        glm::vec3 getLastRecordedPositionOfOpponent(ARCS::Entity* enemie) const;
        void setLastRecordedPositionOfOpponent(ARCS::Entity*, glm::vec3&, float&);
        float getTimeOpponentHasBeenVisible(ARCS::Entity* enemie) const; 
        float getTimeSinceLastSensed(ARCS::Entity* enemie) const; 
        float getTimeOpponentHasBeenOutOfView(ARCS::Entity* enemie) const;
        MemoryRecord& getMemoryRecordFromMap(ARCS::Entity*); 
        bool isOponentHittable(ARCS::Entity* enemie); 
        bool isWithinFOV(ARCS::Entity* enemie);
        bool isSensed(ARCS::Entity* enemie);
        bool isAnyStrange(ARCS::Entity* enemie);
        void setAnyStrange(ARCS::Entity* enemie);
        void registEnt2React(ARCS::Entity&);
        void check2React(ARCS::Entity&, ARCS::CollisionSystem&);
};