#include <components/Entity.hpp>
#include "FacadeIrrPhysics.hpp"




bool
FacadeIrrPhysics::update(ARCS::PositionComponent &pos) {
    scene::ISceneNode* node = irrlicht.smgr->getSceneNodeFromId( pos.getEntityID() );
    
    if (node) {
        node->setPosition( irrlicht.glm3fcore( pos.position ) );
        node->setRotation( irrlicht.glm3fcore( pos.rotation ) );
    }

    return true;
}




void
FacadeIrrPhysics::createEnemiesPatrol() {
    //std::vector<core::vector3df> p;
    //p.reserve(10);
//
    //vector3df punto11(298,150,50), punto12(298,150,35), punto21(445,150,50), punto22(445,150,35),
    //punto13(298,150,150), punto23(445,150,130);
    //p.push_back(punto11);
    //p.push_back(punto21);
    //p.push_back(punto23);
    //p.push_back(punto21);
    //p.push_back(punto11);
    //p.push_back(punto13);
    //pointPatrol.push_back(p);
    //waiting[0] = 0;
    //next[0] = 0;
    //quiet[0] = false;
    //alert[0] = false;
    //hiting[0] = false;
    //waitingAttack[0] = WEAPON_ATTACK_WAITING/2;
    //attackMaxDistance[0] = core::vector3df(0,0,-1);
    //attackMaxMovement[0] = core::vector3df(0,0,0);
//
    //vector3df enemy2Punt1(691,150,207), enemy2Punt2(691,150,110), enemy2Punt3(838,150,110), enemy2Punt4(838,150,58),
    //enemy2Punt5(957,150,59);
    //p.clear();
    //p.push_back(enemy2Punt1);
    //p.push_back(enemy2Punt2);
    //p.push_back(enemy2Punt3);
    //p.push_back(enemy2Punt4);
    //p.push_back(enemy2Punt5);
    //p.push_back(enemy2Punt4);
    //p.push_back(enemy2Punt3);
    //p.push_back(enemy2Punt2);
    //pointPatrol.push_back(p);
    //waiting[1] = 0;
    //next[1] = 0;
    //quiet[1] = false;
    //alert[1] = false;
    //hiting[1] = false;
    //waitingAttack[1] = WEAPON_ATTACK_WAITING/2;
    //attackMaxDistance[1] = vector3df(0,0,-1);
    //attackMaxMovement[1] = vector3df(0,0,0);
//
    //vector3df enemy3Punt1(629,150,-42), enemy3Punt2(779,150,-42);
    //p.clear();
    //p.push_back(enemy3Punt1);
    //p.push_back(enemy3Punt2);
    //pointPatrol.push_back(p);
    //waiting[2] = 0;
    //next[2] = 0;
    //quiet[2] = false;
    //alert[2] = false;
    //hiting[2] = false;
    //waitingAttack[2] = WEAPON_ATTACK_WAITING/2;
    //attackMaxDistance[2] = vector3df(0,0,-1);
    //attackMaxMovement[2] = vector3df(0,0,0);
//
    //core::vector3df enemy4Punt1(1368,150,-6), enemy4Punt2(1368,150,-34), enemy4Punt3(1118,150,-34), enemy4Punt4(1118,150,-124);
    //p.clear();
    //p.push_back(enemy4Punt1);
    //p.push_back(enemy4Punt2);
    //p.push_back(enemy4Punt3);
    //p.push_back(enemy4Punt4);
    //p.push_back(enemy4Punt2);
    //p.push_back(enemy4Punt3);
    //pointPatrol.push_back(p);
    //waiting[3] = 0;
    //next[3] = 0;
    //quiet[3] = false;
    //alert[3] = false;
    //hiting[3] = false;
    //waitingAttack[3] = WEAPON_ATTACK_WAITING/2;
    //attackMaxDistance[3] = vector3df(0,0,-1);
    //attackMaxMovement[3] = vector3df(0,0,0);
//
    //core::vector3df enemy5Punt1(1519,150,-319), enemy5Punt2(912,150,-319);
    //p.clear();
    //p.push_back(enemy5Punt1);
    //p.push_back(enemy5Punt2);
    //pointPatrol.push_back(p);
    //waiting[4] = 0;
    //next[4] = 0;
    //quiet[4] = false;
    //alert[4] = false;
    //hiting[4] = false;
    //waitingAttack[4] = WEAPON_ATTACK_WAITING/2;
    //attackMaxDistance[4] = vector3df(0,0,-1);
    //attackMaxMovement[4] = vector3df(0,0,0);
//
    //core::vector3df enemy6Punt1(1406,150,173), enemy6Punt2(1491,150,173), enemy6Punt3(1491,150,70);
    //p.clear();
    //p.push_back(enemy6Punt1);
    //p.push_back(enemy6Punt2);
    //p.push_back(enemy6Punt3);
    //p.push_back(enemy6Punt2);
    //pointPatrol.push_back(p);
    //waiting[5] = 0;
    //next[5] = 0;
    //quiet[5] = false;
    //alert[5] = false;
    //hiting[5] = false;
    //waitingAttack[5] = WEAPON_ATTACK_WAITING/2;
    //attackMaxDistance[5] = vector3df(0,0,-1);
    //attackMaxMovement[5] = vector3df(0,0,0);
//
    //core::vector3df enemy7Punt1(1387,150,144), enemy7Punt2(1387,150,118), enemy7Punt3(1316,150,118), enemy7Punt4(1316,150,71),
    //enemy7Punt5(1237,150,70);
    //p.clear();
    //p.push_back(enemy7Punt1);
    //p.push_back(enemy7Punt2);
    //p.push_back(enemy7Punt3);
    //p.push_back(enemy7Punt4);
    //p.push_back(enemy7Punt5);
    //p.push_back(enemy7Punt4);
    //p.push_back(enemy7Punt3);
    //p.push_back(enemy7Punt2);
    //pointPatrol.push_back(p);
    //waiting[6] = 0;
    //next[6] = 0;
    //quiet[6] = false;
    //alert[6] = false;
    //hiting[6] = false;
    //waitingAttack[6] = WEAPON_ATTACK_WAITING/2;
    //attackMaxDistance[6] = vector3df(0,0,-1);
    //attackMaxMovement[6] = vector3df(0,0,0);
//
    //core::vector3df enemy8Punt1(1066,150,403), enemy8Punt2(1256,150,403), enemy8Punt3(1256,150,354), enemy8Punt4(1388,150,354),
    //enemy8Punt5(1388,150,180);
//
    //p.clear();
    //p.push_back(enemy8Punt1);
    //p.push_back(enemy8Punt2);
    //p.push_back(enemy8Punt3);
    //p.push_back(enemy8Punt4);
    //p.push_back(enemy8Punt5);
    //p.push_back(enemy8Punt4);
    //p.push_back(enemy8Punt3);
    //p.push_back(enemy8Punt2);
    //pointPatrol.push_back(p);
    //waiting[7] = 0;
    //next[7] = 0;
    //quiet[7] = false;
    //alert[7] = false;
    //hiting[7] = false;
    //waitingAttack[7] = WEAPON_ATTACK_WAITING/2;
    //attackMaxDistance[7] = vector3df(0,0,-1);
    //attackMaxMovement[7] = vector3df(0,0,0);
}




void
FacadeIrrPhysics::startCollisionPlayerMap(ARCS::Entity& e){ 
    //core::aabbox3d<f32> box = irrlicht.smgr->getSceneNodeFromId(e.id)->getBoundingBox();
    //core::vector3df radius = box.MaxEdge - box.getCenter();
    //auto& anim = animators.emplace_back(irrlicht.smgr->createCollisionResponseAnimator(selector,irrlicht.smgr->getSceneNodeFromId(e.id),(radius * 5),
    //    core::vector3df(0, -10, 0), core::vector3df(0,2,0)));
    //irrlicht.smgr->getSceneNodeFromId(e.id)->addAnimator(anim);
    //anim->drop();
}




void
FacadeIrrPhysics::startCollisionCamMap(){ 
    //core::aabbox3d<f32> box = irrlicht.smgr->getActiveCamera()->getBoundingBox();
    //core::vector3df radius = box.MaxEdge - box.getCenter();
    //auto* animatorCam = irrlicht.smgr->createCollisionResponseAnimator(selector,irrlicht.smgr->getActiveCamera(), vector3df(5,5,5),
    //    core::vector3df(0, -10, 0), core::vector3df(0, 5, 0));
//
    //irrlicht.smgr->getActiveCamera()->addAnimator(animatorCam);
    //animatorCam->drop();
    //anim->drop();
    //smgr->addCameraSceneNodeFPS(0,100,0.07);       //     TODO << Visual Debug
}




void
FacadeIrrPhysics::initSelector(ARCS::Entity &e){
    //selector = irrlicht.smgr->createOctreeTriangleSelector(((IMeshSceneNode*)irrlicht.smgr->getSceneNodeFromId(e.id))->getMesh(),irrlicht.smgr->getSceneNodeFromId(e.id),128);
    //irrlicht.smgr->getSceneNodeFromId(e.id)->setTriangleSelector(selector);
}



void
FacadeIrrPhysics::dropSelector(){
    //selector->drop();
}




void
FacadeIrrPhysics::addChild(const int parentID, const int childID) {
    scene::ISceneNode* parent { irrlicht.smgr->getSceneNodeFromId( parentID ) };
    scene::ISceneNode* child  { irrlicht.smgr->getSceneNodeFromId( childID ) };

    if ( !parent  ||  !child ) return;
    parent->addChild(child);
}



void
FacadeIrrPhysics::setMeshPosition(const int id, const glm::vec3& position) {
    scene::ISceneNode* node = irrlicht.smgr->getSceneNodeFromId( id );
    
    if (node) node->setPosition(irrlicht.glm3fcore( position ));
}



void
FacadeIrrPhysics::setMeshRotation(const int id, const glm::vec3& position) {
    scene::ISceneNode* node = irrlicht.smgr->getSceneNodeFromId( id );
    
    if (node) node->setRotation(irrlicht.glm3fcore( position ));
}