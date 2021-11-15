#pragma once

#include "LimitedTrigger.hpp"
#include <manager/GameContext.hpp>


class EnemyDown : public LimitedTrigger
{
private:
    
public:
    EnemyDown(int t,int p);

    bool Try(ARCS::GameContext& gc,ARCS::CollisionSystem& cs, float delta);
};

