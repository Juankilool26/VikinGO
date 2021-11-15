#include "LimitedTrigger.hpp"



LimitedTrigger::LimitedTrigger(int time,int p)
    : Trigger  { p }
    , lifeTime { time }
{ }



void
LimitedTrigger::Update(float delta) {
    if(lifeTime <= 0){
        setToBeRemoved();
    }
}