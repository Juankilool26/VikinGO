#include "FacadeLVRender.hpp"
#include <components/Entity.hpp>

bool FacadeLVRender::update() const{
    return leviatan.device->update(leviatan.device->getWindow(), 10);
}

void
FacadeLVRender::doActionAnimation(int id, int questAnim){
    if(leviatan.device->getSmgr()->getNodeById(id)){
        auto* entity = leviatan.device->getSmgr()->getNodeById(id)->getEntity();
        if(LVMesh* mesh = dynamic_cast <LVMesh *>(entity)){
            mesh->doAnimation(questAnim);
        }
    }
}

void
FacadeLVRender::updateAnimation(int id){
    if(leviatan.device->getSmgr()->getNodeById(id)){
        auto* entity = leviatan.device->getSmgr()->getNodeById(id)->getEntity();
        if(LVMesh* mesh = dynamic_cast <LVMesh *>(entity)){
            mesh->animate();
        }
    }
}

void 
FacadeLVRender::paintChargeScreen(){
    leviatan.device->changeCharging();
}

bool FacadeLVRender::isDeviceRunning() {
    return leviatan.device->isDeviceRunning();
}
void FacadeLVRender::dropDevice() { //Si que se usa
    leviatan.device->closeWindow();
}
void FacadeLVRender::cleanScene() { //Si que se usa
    leviatan.device->getSmgr()->clean();
} 

glm::vec2
FacadeLVRender::getScreenSize() {
    return glm::vec2{WIDTH, HEIGHT};
}

void FacadeLVRender::createAnimatedNode(const ARCS::Entity & e) {
    createStaticNode( e.id, e.pos->position, e.pos->rotation, e.rend->object.data() );
    auto* node { leviatan.device->getSmgr()->getNodeById(e.id) };

    if(node->getNodeId()==1){
        e.rend->animated = true;
        auto keyFrames = leviatan.device->getSmgr()->getResourceManager().GetResourceAnimation("media/models/animations/prota/protagonista","protagonista",7);
        auto* entity = leviatan.device->getSmgr()->getNodeById(e.id)->getEntity();
        if(LVMesh* mesh = dynamic_cast <LVMesh *>(entity)){
            mesh->createAnimation(0,keyFrames,false);
        }
    }

    if ( node  &&  e.heal  &&  !e.inp ) {
        if (e.ai) {
            auto* mesh = leviatan.device->getSmgr()->getResourceManager().getMesh("media/models/zalertaEnemigo.obj");
            std::shared_ptr<LVNode> nodeAlert = std::make_shared<LVNode>();
            std::shared_ptr<LVMesh> entMesh = std::make_shared<LVMesh>();
            entMesh->setMesh(mesh);
            nodeAlert->setEntity( std::move(entMesh) );
            nodeAlert->setNodeId((e.id + 5000));
            nodeAlert->setVisible(false);
            node->addChild( std::move(nodeAlert) );

            if(e.heal->health == 5){
                e.rend->animated = true;
                auto keyFrames = leviatan.device->getSmgr()->getResourceManager().GetResourceAnimation("media/models/animations/blind/blindWalking","blind",10);
                auto keyFrames2 = leviatan.device->getSmgr()->getResourceManager().GetResourceAnimation("media/models/animations/blindAttack/blindAttack","blind",9);
                auto keyFrames3 = leviatan.device->getSmgr()->getResourceManager().GetResourceAnimation("media/models/animations/blindRunning/blindRunning","blind",8);
                auto keyFrames4 = leviatan.device->getSmgr()->getResourceManager().GetResourceAnimation("media/models/animations/blindHurt/blindHurt","blind",24);
                auto* entity = leviatan.device->getSmgr()->getNodeById(e.id)->getEntity();
                if(LVMesh* mesh = dynamic_cast <LVMesh *>(entity)){
                    mesh->createAnimation(0,keyFrames,true); //Walk id = 0
                    mesh->createAnimation(1,keyFrames2,false); //Attack id = 1
                    mesh->createAnimation(2,keyFrames3,true); //Run id = 2
                    mesh->createAnimation(3,keyFrames4,false); //Hurt id = 3
                    mesh->doAnimation(0);
                }
            }
            else if(!e.arr && e.sens->rSense.vision.positionRelative.y < 500){
                e.rend->animated = true;
                auto keyFrames = leviatan.device->getSmgr()->getResourceManager().GetResourceAnimation("media/models/animations/patroler/patrollerWalking","patroler",20);
                auto keyFrames2 = leviatan.device->getSmgr()->getResourceManager().GetResourceAnimation("media/models/animations/patrolerAttack/patrolerAttack","patroler",8);
                auto keyFrames3 = leviatan.device->getSmgr()->getResourceManager().GetResourceAnimation("media/models/animations/patrolerRunning/patrolerRunning","patroler",15);
                auto keyFrames4 = leviatan.device->getSmgr()->getResourceManager().GetResourceAnimation("media/models/animations/patrolerHurt/patrolerHurt","patroler",7);
                auto* entity = leviatan.device->getSmgr()->getNodeById(e.id)->getEntity();
                if(LVMesh* mesh = dynamic_cast <LVMesh *>(entity)){
                    mesh->createAnimation(0,keyFrames,true); //Walk id = 0
                    mesh->createAnimation(1,keyFrames2,false); //Attack id = 1
                    mesh->createAnimation(2,keyFrames3,true); //Run id = 2
                    mesh->createAnimation(3,keyFrames4,false); //Hurt id = 3
                    mesh->doAnimation(0);
                }
                    
            }
            else if(e.arr){
                e.rend->animated = true;
                auto keyFrames = leviatan.device->getSmgr()->getResourceManager().GetResourceAnimation("media/models/arquero","arquero",1);
                auto* entity = leviatan.device->getSmgr()->getNodeById(e.id)->getEntity();
                if(LVMesh* mesh = dynamic_cast <LVMesh *>(entity)){
                    mesh->createAnimation(0,keyFrames,false);
                    mesh->createAnimation(1,keyFrames,false);
                    mesh->createAnimation(2,keyFrames,false);
                    mesh->createAnimation(3,keyFrames,false);
                    mesh->doAnimation(0);
                }
            }
        }
        
        createStaticNode( e.id + 6000, e.pos->position, e.pos->rotation, "media/models/vidaEnemigo.obj" );
        LVMesh* m = static_cast<LVMesh*>(leviatan.device->getSmgr()->getNodeById(e.id + 6000)->getEntity());
        m->setTexture("vidaEnemigo5");
    }
} 

void FacadeLVRender::createStaticNode(const ARCS::Entity &e) {
    createStaticNode( e.id, e.pos->position, e.pos->rotation, e.rend->object.data() );
}

void FacadeLVRender::createStaticNode(const glm::vec3 pos, const glm::vec3 rot, const std::string_view obj) {
    createStaticNode( -1, pos, rot, obj.data() );
}

void FacadeLVRender::createStaticNode(const int id, const glm::vec3 pos, const glm::vec3 rot, const std::string_view obj){
    LVNode* node = leviatan.device->getSmgr()->addSceneNodeMesh( obj.data() );
    node->setPosition( pos );
    node->setRotation( rot );
    node->setNodeId( id );
}

void FacadeLVRender::createFPSCameraNode(const ARCS::Entity &e) { //Si que se usa
    leviatan.device->createFPSCameraNode(e.id, e.pos->position, e.cam->lookat);
}
void FacadeLVRender::setCameraTarget(const ARCS::CameraComponent &cam) {  //Si que se usa
    leviatan.device->setCameraTarget(cam.getEntityID(),cam.lookat);
}
void FacadeLVRender::setCameraPosition(const ARCS::Entity &) { //Si que se usa
}
glm::vec2 FacadeLVRender::getScreenCenterPosition() const { //Si que se usa
    return leviatan.device->getScreenCenterPosition();
}
void FacadeLVRender::setNoVisible(const int id) { //Si que se usa
    setVisible(id, false);
}
void FacadeLVRender::setVisible(const int id) { //Si que se usa
    setVisible(id, true);
}

// ESTO NECESITAMOS USARLO AUN DE IRRLICHT (SE USAN TODAS)

void FacadeLVRender::setVisible(const int id, bool vis){
    auto* node { leviatan.device->getSmgr()->getNodeById(id) };
    if ( node ) node->setVisible(vis);
}

void FacadeLVRender::setTransparent(const int id) {

}

void FacadeLVRender::hudInit() {

}

void FacadeLVRender::menuInit() {
    leviatan.device->menuInit();
    menuOptions(1);
}

void FacadeLVRender::pauseInit(bool die) {
    if(die)
        leviatan.device->drawDeath(true);
    else
        leviatan.device->drawPause(true);
}

void FacadeLVRender::interInit() {
    leviatan.device->drawInter(true);
}

void FacadeLVRender::drawHud(const ARCS::Entity &e) {
    if(e.heal){
        leviatan.device->drawHud(e.heal->health);
    }
}

void FacadeLVRender::menuOptions(int opt) {
    leviatan.device->menuOptions(opt);
}

void FacadeLVRender::secondaryInit(int opt){
    leviatan.device->secondaryInit(opt);
}

void FacadeLVRender::pauseClean() {
    leviatan.device->drawPause(false);
}

void FacadeLVRender::keyHUD(int) {
    leviatan.device->keyHUD();
}

void FacadeLVRender::drawConver(int con) {
    leviatan.device->drawConver(con);
}

void FacadeLVRender::drawStealthBar(int t) {
   leviatan.device->drawStealBar(t);
   clearKeyHUD(0);
}

void FacadeLVRender::clearKeyHUD(int id) {
    leviatan.device->clearKeyHUD(id);
}

void FacadeLVRender::orbHUD() {
    leviatan.device->drawOrb(true);
}

void FacadeLVRender::interClean() {
    leviatan.device->drawInter(false);
}

void FacadeLVRender::initStam() {

}

void FacadeLVRender::drawStam(const ARCS::Entity &e) {
    if(e.inp){
        leviatan.device->drawStam(e.inp->stamina);
    }
}

void FacadeLVRender::drawHudDeath() {
    leviatan.device->drawHud(0);
}

void FacadeLVRender::drawSeen(bool seen) {
    leviatan.device->drawSeen(seen);
}

void FacadeLVRender::clearHudDeath() {
    leviatan.device->drawDeath(false);
}

void FacadeLVRender::clearHudLife() {

}

void FacadeLVRender::clearConver() {
    leviatan.device->stopTalking();
}

void FacadeLVRender::textKey(int) {

}

void FacadeLVRender::clearTextKey(int) {

}

void FacadeLVRender::textOrb() {

}

void FacadeLVRender::clearTextOrb() {

}

void FacadeLVRender::drawKill() {
    leviatan.device->drawKill(true);
}

void FacadeLVRender::clearKill() {
    leviatan.device->drawKill(false);
}

void FacadeLVRender::setSkybox(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back){
    leviatan.device->setSkybox(right, left, top, bottom, front, back);
}

void FacadeLVRender::setTextureNode(int id,std::string_view name) {
    leviatan.device->setNodeTexture(id, name);
}

void  FacadeLVRender::addSceneDirectionalNodeLight(glm::vec3 dir, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, bool on){
    leviatan.device->getSmgr()->addSceneDirectionalNodeLight(dir, amb, diff, spec, on);
}
void  FacadeLVRender::addScenePointNodeLight(glm::vec3 pos, float constant, float linear, float quadratic, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, bool on){
    leviatan.device->getSmgr()->addScenePointNodeLight(pos, constant, linear, quadratic, amb, diff, spec, on);
}
void  FacadeLVRender::addSceneSpotNodeLight(glm::vec3 pos, glm::vec3 dir, float constant, float linear, float quadratic, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float innerCut, float outerCut, bool on){
    leviatan.device->getSmgr()->addSceneSpotNodeLight(pos, dir, constant, linear, quadratic, amb, diff, spec, innerCut, outerCut, on);
}

void FacadeLVRender::deleteLights(){
    leviatan.device->getSmgr()->deleteLights();
}
void FacadeLVRender::setWindowTitle(std::string_view&& title) {
    leviatan.device->setWindowTitle(std::move(title));
}