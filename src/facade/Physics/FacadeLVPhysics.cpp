#include <components/Entity.hpp>
#include "FacadeLVPhysics.hpp"

bool FacadeLVPhysics::update(ARCS::PositionComponent & pos){
    LVGL::LVNode* node = leviatan.device->getSmgr()->getNodeById(pos.getEntityID());
    
    if (node) {
        if(node->getNodeId() != 2)
        {   
            node->setPosition( pos.position );
            node->setRotation( pos.rotation );
        }
        else  
        {
            leviatan.device->getSmgr()->getCamera()->setPos( pos.position );
        }
    }

    return true;
}

void FacadeLVPhysics::setMeshPosition(const int id,const glm::vec3 &pos){
    LVGL::LVNode* node = leviatan.device->getSmgr()->getNodeById(id);
    if ( node ) node->setPosition( pos );
}
void FacadeLVPhysics::setMeshRotation(const int id,const glm::vec3 &rot){
    LVGL::LVNode* node = leviatan.device->getSmgr()->getNodeById(id);
    if ( node ) node->setRotation( rot );
}

void FacadeLVPhysics::createEnemiesPatrol(){

}
void FacadeLVPhysics::startCollisionPlayerMap(ARCS::Entity& e){

}
void FacadeLVPhysics::startCollisionCamMap(){

}
void FacadeLVPhysics::initSelector(ARCS::Entity& e){

}
void FacadeLVPhysics::dropSelector(){

}

 void FacadeLVPhysics::addChild(const int ,const int ){

 }