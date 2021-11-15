#include "ChasePlayer.hpp"


bool
ChasePlayer::run(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map)
{

    ai.moving = ai.pointing = true;
    ai.target = mr.lastSensePosition;
    
    return true;
}

/*
{
    bool chase { false };

    if ( mr.hittable ) {
        ai.moving = false;
        if ( wp.hiting  &&  wp.time2HitAgain < wp.limitTime4Waiting ) {
            ai.target = mr.lastSensePosition;
            ai.pointing = true;
        } else {
            ai.pointing = false;
        }
        return chase;
    } else if ( !mr.hittable  &&  wp.hiting  &&  wp.displacement >= wp.limitDistance4Attacking ) {
        wp.hiting = false;
        wp.displacement = 0;
        wp.wpositionRelative.x = wp.wpositionRelative.z = 0;
        ai.pointing = ai.moving = true;
    }
    
    // When enemy can not find player go to last position detected
    ai.pointing = ai.moving = ( glm::distance(ai.target, pos.position) > ai.kMinRange2Stop );

    if(ai.beetween || roundObstacle){
        ai.target = v;
        roundObstacle = true;
    }
    else
        ai.target = mr.lastSensePosition;

    if(glm::distance(pos.position,v) <= ai.kMinRange2Stop){
        roundObstacle = false;
        ai.target = mr.lastSensePosition;
    }

    chase = true;
    return chase;
}
*/