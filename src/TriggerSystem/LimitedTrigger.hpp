#pragma once

#include "Trigger.hpp"

struct LimitedTrigger: public Trigger
{

    explicit LimitedTrigger(int time,int p);

    void Update(float delta) override;
    //bool Try(ARCS::GameContext&,ARCS::CollisionSystem&) override;

protected:
    int lifeTime;

};
