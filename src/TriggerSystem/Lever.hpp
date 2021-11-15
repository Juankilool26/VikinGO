#pragma once

#include "RespawningTrigger.hpp"
#include <manager/GameContext.hpp>
#include <facade/Render/ManFacadeRender.hpp>
#include <facade/Input/ManFacadeInput.hpp>
#include <util/KeyCodes.hpp>



class Lever : public RespawningTrigger
{

private:
    bool actioned = false;
    int entDoor;


public:
    explicit Lever(int p, int d);

    bool Try(ARCS::GameContext& gc, ARCS::CollisionSystem& cs, float delta) override;

};




