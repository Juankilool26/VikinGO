#pragma once

#include <RecordMemory/SensoryMemory.hpp>



namespace ARCS {



struct GameContext;
struct CollisionSystem;


class BehaviourSystem {
    
public:
    explicit BehaviourSystem(SensoryMemory&);
    ~BehaviourSystem() = default;
    bool update(GameContext &, CollisionSystem &) const noexcept;


private:
    SensoryMemory& sMemory;
    unsigned int getFarPointPatrol(GameContext &gc,std::vector<glm::vec3> pointsPatrol, int mapId) const;
    void checkObstacle(GameContext &gc, CollisionSystem &colsys,Entity &ent) const;

};



} // namespace ARCS