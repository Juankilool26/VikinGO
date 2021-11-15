#pragma once

#include "LimitedTrigger.hpp"
#include "RespawningTrigger.hpp"
#include <manager/GameContext.hpp>
#include <facade/Render/ManFacadeRender.hpp>
#include <facade/Input/ManFacadeInput.hpp>
#include <util/KeyCodes.hpp>
#include <facade/Render/FacadeIrrRender.hpp>


class Key : public LimitedTrigger {
    private:
        bool taked = false;
        int entDoor;
        int id = 0;

    public:
        explicit Key(int t, int p, int d, int);
        bool Try(ARCS::GameContext& gc, ARCS::CollisionSystem& cs, float delta);
};
