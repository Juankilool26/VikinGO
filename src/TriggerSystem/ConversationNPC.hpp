#pragma once

#include "RespawningTrigger.hpp"
#include <facade/Sound/ManFacadeSound.hpp>
#include <facade/Input/ManFacadeInput.hpp>
#include <util/KeyCodes.hpp>
#include <string>


class ConversationNPC : public RespawningTrigger
{
private:
    KeySound key;
    bool talking = false;
    int id = 0;

public:
    ConversationNPC(int p, KeySound key_,int);
    bool Try(ARCS::GameContext& gc, ARCS::CollisionSystem& cs, float delta) override;
  
};