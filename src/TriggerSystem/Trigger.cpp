#include "Trigger.hpp"



Trigger::Trigger(int eid)
    : entID { eid }
{ }



bool 
Trigger::intersects(ARCS::CollisionSystem& cs, glm::vec3 pos, ARCS::Entity& player){
    boxRootRangeTrigger.collided = false;
    cs.checkObjectCollision(boxRootRangeTrigger,player.col->boxRoot,pos,player.pos->position);
    return boxRootRangeTrigger.collided;
}



float
Trigger::animationSpeed { 135.f };