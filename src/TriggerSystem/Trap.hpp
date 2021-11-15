#pragma once

#include "LimitedTrigger.hpp"
#include <manager/GameContext.hpp>
#include <facade/Render/ManFacadeRender.hpp>
#include <facade/Input/ManFacadeInput.hpp>
#include <util/KeyCodes.hpp>


class Trap : public LimitedTrigger
{


private:
    bool taked = false;
    int entDoor;


public:
    explicit Trap(int t,int p);
    bool Try(ARCS::GameContext& gc, ARCS::CollisionSystem& cs, float delta);


};