#include "AttackPlayer.hpp"
#include <facade/Render/ManFacadeRender.hpp>


bool
AttackPlayer::run(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map)
{
    wp.hiting = true;
    ai.moving = false;
    if ( wp.time2HitAgain < wp.limitTime4Waiting ) {
        ai.target = mr.lastSensePosition;
        ai.pointing = true;
        wp.hiting = false;
    } else {
        ManFacadeRender::GetInstance()->getFacade()->doActionAnimation(ai.getEntityID(),1);
        ai.pointing = false;
    }

    return true;
}