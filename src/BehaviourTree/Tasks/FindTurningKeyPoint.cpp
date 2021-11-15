#include "FindTurningKeyPoint.hpp"


bool
FindTurningKeyPoint::run(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map)
{
    auto currentPointID { map.getClosestKeyPoint(ai.pointsPatrol[ai.actualPoint]) };
    if(currentPointID == ai.currentPointMapID){
        ai.inPatrol = true;
    }

    if(glm::distance(pos.position, map.getKeyPointByID(ai.currentPointMapID)) <= ai.kMinRange2Stop){
        if(currentPointID > ai.currentPointMapID){
            ++ai.currentPointMapID;
        }else{
            --ai.currentPointMapID;
        }                    
    }

    ai.target = map.getKeyPointByID(ai.currentPointMapID);
    ai.moving = ai.pointing = true;

    return true;
}