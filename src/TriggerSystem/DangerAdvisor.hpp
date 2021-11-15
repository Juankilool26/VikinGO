#pragma once

#include "RespawningTrigger.hpp"
#include <manager/GameContext.hpp>
#include <facade/Render/ManFacadeRender.hpp>
#include <facade/Input/ManFacadeInput.hpp>
#include <facade/Sound/ManFacadeSound.hpp>
#include <util/KeyCodes.hpp>
#include <string_view>



class DangerAdvisor : public RespawningTrigger
{

private:
   KeySound key; 

public:
    explicit DangerAdvisor(int p,KeySound s);
    bool Try(ARCS::GameContext& gc, ARCS::CollisionSystem& cs, float delta) override;

};