#pragma once

#include "Trigger.hpp"

class RespawningTrigger : public Trigger{

protected:
    float updatesBetweenRespawns;
    float updatesRemainingUntilRespawn;

    float timeTalking = 0;
    float kTimeLimit = 0.25;

    void Desactivate();

public:
    RespawningTrigger(int p);

    //bool Try(ARCS::GameContext&, ARCS::CollisionSystem&) override;
    void Update(float) override;

    void SetRespawnDelay(unsigned int);
        
};