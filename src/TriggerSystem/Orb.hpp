#pragma once

#include "LimitedTrigger.hpp"
#include <manager/GameContext.hpp>
#include <facade/Render/ManFacadeRender.hpp>
#include <facade/Input/ManFacadeInput.hpp>
#include <util/KeyCodes.hpp>


class Orb : public LimitedTrigger
{


private:
    bool taked = false;
    int entDoor;


public:
    explicit Orb(int t,int p, int d);
    bool Try(ARCS::GameContext& gc, ARCS::CollisionSystem& cs, float delta);


};