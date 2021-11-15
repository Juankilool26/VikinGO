#include "RespawningTrigger.hpp"



RespawningTrigger::RespawningTrigger(int p)
    : Trigger(p)
{ }



void
RespawningTrigger::Update(float delta) {
    updatesRemainingUntilRespawn -= delta;
    timeTalking += delta;
    if((updatesRemainingUntilRespawn <= 0) && !isActive()){
        setActive();
    }
}




void
RespawningTrigger::Desactivate()
{
    setInactive();
    updatesRemainingUntilRespawn = updatesBetweenRespawns;
}