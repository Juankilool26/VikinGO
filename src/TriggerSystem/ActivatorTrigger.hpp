#pragma once

#include "RespawningTrigger.hpp"
#include <facade/Sound/ManFacadeSound.hpp>
#include <facade/Input/ManFacadeInput.hpp>
#include <util/KeyCodes.hpp>

class ActivatorTrigger : public RespawningTrigger
{
private:
    Trigger& activate;
    int activateEnt = 0;
public:

    ActivatorTrigger(int p,Trigger&);
    bool Try(ARCS::GameContext& gc, ARCS::CollisionSystem& cs, float delta) override;
  
};