#include <components/Entity.hpp>
#include <facade/Render/FacadeIrrRender.hpp>

//#define PL_MPEG_IMPLEMENTATION
//#include <../lib/pl_mpeg/src/pl_mpeg.h>
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include <../lib/pl_mpeg/src/stb_image_write.h>

bool
FacadeIrrRender::update() const {
    irrlicht.driver->beginScene(true, true, video::SColor(255, 100, 101, 140));
    irrlicht.device->setWindowCaption(L"VikinGO");
    irrlicht.smgr->drawAll();
    irrlicht.guienv->drawAll();
    irrlicht.driver->endScene();
    return irrlicht.device->run();
}

void FacadeIrrRender::cleanScene(){
    irrlicht.smgr->clear();
    irrlicht.guienv->clear();
   
    lifeContainer   = nullptr;
    mainMenu        = nullptr;
    pause           = nullptr;
    key             = nullptr ;
    orb             = nullptr;       
    inter           = nullptr;                 
    stam            = nullptr;                    
    death           = nullptr;                  
    conver          = nullptr;                 
    barStealth      = nullptr;             
    eye             = nullptr;                 
    textKeyPick     = nullptr;            
    textOrbPick     = nullptr;           
    enemyLife       = nullptr;            
    kill            = nullptr;               
}


glm::vec2
FacadeIrrRender::getScreenSize() {
    return glm::vec2{kScreenWidth, kScreenHeight};
}


bool
FacadeIrrRender::isDeviceRunning() {
    if (irrlicht.device  &&  irrlicht.device->run())
        return true;
    else
        return false;
}

void
FacadeIrrRender::dropDevice() {
    irrlicht.device->closeDevice();
}

void
FacadeIrrRender::createAnimatedNode(const ARCS::Entity &e) {
    scene::IAnimatedMeshSceneNode* node { irrlicht.smgr->addAnimatedMeshSceneNode( irrlicht.smgr->getMesh(e.rend->object.data()) ) };
    node->setMaterialFlag(video::EMF_LIGHTING, false);
    node->setID(e.id);

    if(e.heal && !e.inp){ // ENEMY
        if (e.ai) {
            scene::IAnimatedMesh* meshEnemy  { irrlicht.smgr->getMesh("media/models/zalertaEnemigo.obj") };
            scene::IMeshSceneNode* nodeEnemy { irrlicht.smgr->addOctreeSceneNode(meshEnemy->getMesh(0), 0) };
            node->addChild(nodeEnemy); // Le meto al node que es el enemigo el modelado que es el ndoe enemy de alerta
            nodeEnemy->setID(e.id + 5000);
            setVisible(nodeEnemy->getID(), false);
            nodeEnemy->setMaterialFlag(video::EMF_LIGHTING, false);
        }
        scene::IAnimatedMesh* meshEnemyLife  { irrlicht.smgr->getMesh("media/models/zvidaEnemigo.obj") };
        scene::IMeshSceneNode* nodeEnemyLife { irrlicht.smgr->addOctreeSceneNode(meshEnemyLife->getMesh(0), 0) };
        //node->addChild(nodeEnemyLife); // Le meto al node que es el enemigo el modelado que es el ndoe enemy vida
        nodeEnemyLife->setID(e.id + 6000);
        setTextureNode(nodeEnemyLife->getID(), "media/Textures/vidaEnemigoFull.bmp");
        nodeEnemyLife->setMaterialFlag(video::EMF_LIGHTING, false);
    }     
}

void
FacadeIrrRender::createStaticNode(const ARCS::Entity &e) {
    scene::IAnimatedMesh* mesh  { irrlicht.smgr->getMesh(e.rend->object.data()) };
    scene::IMeshSceneNode* node { irrlicht.smgr->addOctreeSceneNode(mesh->getMesh(0), 0) };
    node->setMaterialFlag(video::EMF_LIGHTING, false);
    node->setID(e.id);
}


void
FacadeIrrRender::createStaticNode(const glm::vec3 pos, const glm::vec3 rot, const std::string_view obj) {
    createStaticNode(-1, pos, rot, obj);
}


void
FacadeIrrRender::createStaticNode(const int id, const glm::vec3 pos, const glm::vec3 rot, const std::string_view obj) {
    scene::IAnimatedMesh* mesh  { irrlicht.smgr->getMesh(obj.data()) };
    scene::IMeshSceneNode* node { irrlicht.smgr->addOctreeSceneNode(mesh->getMesh(0), 0) };
    node->setMaterialFlag(video::EMF_LIGHTING, false);
    node->setPosition( irrlicht.glm3fcore(pos) );
    node->setRotation( irrlicht.glm3fcore(rot) );
    node->setID(id);
}


void
FacadeIrrRender::createFPSCameraNode(const ARCS::Entity &ecam) {
    ICameraSceneNode* camNode = irrlicht.smgr->addCameraSceneNode();
    camNode->setID(ecam.id);
    camNode->setPosition( irrlicht.glm3fcore(ecam.pos->position) );
    camNode->setFarValue(50);
    setCameraTarget(*ecam.cam);
    //irrlicht.smgr->addCameraSceneNode(0, core::vector3df(0,50,0), core::vector3df(0,0,0));
}

void
FacadeIrrRender::setCameraTarget(const ARCS::CameraComponent &camcmp) {
    ICameraSceneNode* camera { static_cast<ICameraSceneNode*>( irrlicht.smgr->getSceneNodeFromId(camcmp.getEntityID()) ) };
    camera->setTarget( irrlicht.glm3fcore(camcmp.lookat) );
}

void
FacadeIrrRender::setCameraPosition(const ARCS::Entity &ecam) {
    ICameraSceneNode* camNode { static_cast<ICameraSceneNode*>( irrlicht.smgr->getSceneNodeFromId(ecam.id))};
    camNode->setPosition( irrlicht.glm3fcore(glm::vec3(ecam.pos->position.x,ecam.pos->position.y - 5 ,ecam.pos->position.z)) );
}


glm::vec2
FacadeIrrRender::getScreenCenterPosition() const {
    return glm::vec2(kScreenWidth/2, kScreenHeight/2);
}

void FacadeIrrRender::setNoVisible(const int id){
    scene::ISceneNode* node = irrlicht.smgr->getSceneNodeFromId(id);
    if (node) node->setVisible(false);
}

void FacadeIrrRender::setVisible(const int id){
    scene::ISceneNode* node = irrlicht.smgr->getSceneNodeFromId(id);
    if (node) node->setVisible(true);
}

void FacadeIrrRender::setVisible(const int id, bool visible){
    scene::ISceneNode* node = irrlicht.smgr->getSceneNodeFromId(id);
    if (node) node->setVisible(visible);
}


void
FacadeIrrRender::setTransparent(const int id) {
    scene::ISceneNode* node = irrlicht.smgr->getSceneNodeFromId(id);
    if (node) node->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
}


/* --- MENU --- */

void FacadeIrrRender::menuInit(){
    //std::string videoFrames[0];
    //int longVideo = videoFrames->length();
    //int frames = 000000;
    //int tiempoVideo;

    mainMenu = irrlicht.guienv->addImage(core::rect<s32>(0, 0, 1280, 720));

    /* ESTO ME SACA LOS FRAMES DE UN VIDEO */
    //plm_t *plm = plm_create_with_filename("media/video.mpeg");
	//
	//plm_set_audio_enabled(plm, FALSE);
	//int w = plm_get_width(plm);
	//int h = plm_get_height(plm);
	//uint8_t *rgb_buffer = (uint8_t *)malloc(w * h * 3);
//
	//char png_name[16];
	//plm_frame_t *frame = NULL;
    //
	//for(int i = 1; frame = plm_decode_video(plm); i++) {
	//	plm_frame_to_rgb(frame, rgb_buffer, w * 3);
	//	sprintf(png_name, "%06d.png", i);
	//	printf("Writing %s\n", png_name);
	//	stbi_write_png(png_name, w, h, 3, rgb_buffer, w * 3);
    //    //videoFrames->push_back(*png_name);
    //    //char frame = png_name.split();
    //    tiempoVideo = frame->time;
	//}

    //for(int i = 0; i < tiempoVideo; i++){
    //    video::ITexture* texture = nullptr;
    //    texture = irrlicht.driver->getTexture("media/textures/00000" + i + ".png");
    //    mainMenu->setImage(texture);
    //}
    
    video::ITexture* texture = nullptr;
    texture = irrlicht.driver->getTexture("media/textures/FondoMenuJugar.png");
    mainMenu->setImage(texture);
    //PARA NUESTRO MOTOR HABRA QUE CARGAR TODAS LAS TEXTURAS A LA VEZ 
    irrlicht.driver->getTexture("media/textures/FondoMenuControles.png");
    irrlicht.driver->getTexture("media/textures/FondoMenuCreditos.png");
    irrlicht.driver->getTexture("media/textures/FondoMenuSalir.png");
}

void FacadeIrrRender::menuOptions(int option){
     video::ITexture* texture = nullptr;

    if(option == 1){
        texture = irrlicht.driver->getTexture("media/textures/FondoMenuJugar.png");
        mainMenu->setImage(texture);   
    }

    if(option == 2){
        texture = irrlicht.driver->getTexture("media/textures/FondoMenuControles.png");
        mainMenu->setImage(texture);   
    }

    if(option == 3){
        texture = irrlicht.driver->getTexture("media/textures/FondoMenuCreditos.png");
        mainMenu->setImage(texture);   
    }

    if(option == 4){
        texture = irrlicht.driver->getTexture("media/textures/FondoMenuSalir.png");
        mainMenu->setImage(texture);   
    }
}

/* --- Controls and credits --- */

void FacadeIrrRender::secondaryInit(int i){
    video::ITexture* texture = nullptr;

    if (i == 0){
        texture = irrlicht.driver->getTexture("media/textures/seleccionSexoFemale.png");
    }
    else if(i == 1){
        texture = irrlicht.driver->getTexture("media/textures/controles.png");   
    }
    else if(i == 2){
        texture = irrlicht.driver->getTexture("media/textures/FondoCreditos.png");
    }
    else if(i == 4){
        texture = irrlicht.driver->getTexture("media/textures/seleccionSexoFemale.png");
    }
    else if(i == 5){
        texture = irrlicht.driver->getTexture("media/textures/seleccionSexoOther.png");
    }
    else if(i == 6){
        texture = irrlicht.driver->getTexture("media/textures/seleccionSexoMale.png");
    }

    mainMenu->setImage(texture); 
}

/* --- PAUSE --- */

void FacadeIrrRender::pauseInit(bool die){
    if(!pause)
        pause = irrlicht.guienv->addImage(core::rect<s32>(0, 0, 1280, 720));
        
    pause->setVisible(true);
    video::ITexture* texture = nullptr;

    if(!die){
        texture = irrlicht.driver->getTexture("media/textures/pause.png");
    }else {
        texture = irrlicht.driver->getTexture("media/textures/gameOver.png");
    }
    
    pause->setImage(texture);    
}

void FacadeIrrRender::pauseClean(){
    if(pause)
        pause->setVisible(false);
}


/* --- INTERACTION --- */

void FacadeIrrRender::interInit(){
    if(!inter)
        inter = irrlicht.guienv->addImage(core::rect<s32>(625, 620, 675, 670));
    inter->setVisible(true);
    video::ITexture* texture = nullptr;
    texture = irrlicht.driver->getTexture("media/textures/tecla_inter.png");
    inter->setImage(texture);    
}

void FacadeIrrRender::interClean(){
    if(inter)
        inter->setVisible(false);
}

/* --- SET TEXTURE --- */

void FacadeIrrRender::setTextureNode(int idEnemy, std::string_view texture){
    scene::ISceneNode* node = irrlicht.smgr->getSceneNodeFromId(idEnemy);
    video::ITexture* textureEnemy = irrlicht.driver->getTexture(texture.data()); 

    node->setMaterialTexture(0, textureEnemy);
}

/* --- HUD LIFE --- */

void FacadeIrrRender::hudInit(){
    lifeContainer = irrlicht.guienv->addImage(core::rect<s32>(0, 720-250, 300, 720));
    conver = irrlicht.guienv->addImage(core::rect<s32>(40, 0, 1240, 720));
    barStealth = irrlicht.guienv->addImage(core::rect<s32>(40, 0, 1240, 720));
    eye = irrlicht.guienv->addImage(core::rect<s32>(40, 0, 1240, 720));
    conver->setVisible(false);
    video::ITexture* texture = irrlicht.driver->getTexture("media/textures/vida6.png"); 
    irrlicht.driver->getTexture("media/textures/vida1.png"); 
    irrlicht.driver->getTexture("media/textures/vida2.png"); 
    irrlicht.driver->getTexture("media/textures/vida3.png"); 
    irrlicht.driver->getTexture("media/textures/vida4.png"); 
    irrlicht.driver->getTexture("media/textures/vida5.png"); 
    irrlicht.driver->getTexture("media/textures/vida0.png");
    lifeContainer->setImage(texture);

    texture = irrlicht.driver->getTexture("media/textures/barraSigilo0.png"); 
    irrlicht.driver->getTexture("media/textures/barraSigilo1.png"); 
    irrlicht.driver->getTexture("media/textures/barraSigilo2.png"); 
    irrlicht.driver->getTexture("media/textures/barraSigilo3.png"); 
    irrlicht.driver->getTexture("media/textures/barraSigilo4.png"); 
    irrlicht.driver->getTexture("media/textures/barraSigiloFull.png"); 
    barStealth->setImage(texture);

    eye->setImage(irrlicht.driver->getTexture("media/textures/unseen.png"));
    //staminaContainer = irrlicht.guienv->addImage(core::rect<s32>(0,0,0,0));    
}

void FacadeIrrRender::drawHud(const ARCS::Entity &player) {
    if(player.heal){
        // IMPORTANTE: esto es nuestro motor sera un getResourceTexture()
        video::ITexture* texture = nullptr;
        int vida = player.heal->health;

        if(vida == 6){
            texture = irrlicht.driver->getTexture("media/textures/vida6.png"); 
            irrlicht.driver->makeColorKeyTexture(texture, SColor(255,255,255,255));
        }

        if(vida == 5){
            texture = irrlicht.driver->getTexture("media/textures/vida5.png");
            irrlicht.driver->makeColorKeyTexture(texture, SColor(255,255,255,255));
        }

        if(vida == 4){
            texture = irrlicht.driver->getTexture("media/textures/vida4.png"); 
            irrlicht.driver->makeColorKeyTexture(texture, SColor(255,255,255,255));
        }

        if(vida == 3){
            texture = irrlicht.driver->getTexture("media/textures/vida3.png");
            irrlicht.driver->makeColorKeyTexture(texture, SColor(255,255,255,255));
        }

        if(vida == 2){
            texture = irrlicht.driver->getTexture("media/textures/vida2.png");
            irrlicht.driver->makeColorKeyTexture(texture, SColor(255,255,255,255));
        }

        if(vida == 1){
            texture = irrlicht.driver->getTexture("media/textures/vida1.png");
            irrlicht.driver->makeColorKeyTexture(texture, SColor(255,255,255,255));
        }

        if(vida == 0){
            texture = irrlicht.driver->getTexture("media/textures/vida0.png");
            irrlicht.driver->makeColorKeyTexture(texture, SColor(255,255,255,255));
        }

        if(texture)
            lifeContainer->setImage(texture); 
            //irrlicht.driver->draw2DImage(texture, vector2di(623, 113));
    }
}

void FacadeIrrRender::clearHudLife(){
    lifeContainer->setVisible(false);
}

void FacadeIrrRender::drawConver(int idConv) {
  
        video::ITexture* texture = nullptr;
    if(idConv == 0){
        texture = irrlicht.driver->getTexture("media/textures/npc1.png"); 
        irrlicht.driver->makeColorKeyTexture(texture, SColor(255,255,255,255));
    }

    if(idConv == 1){
        texture = irrlicht.driver->getTexture("media/textures/npc2.png");
        irrlicht.driver->makeColorKeyTexture(texture, SColor(255,255,255,255));
    }

    if(idConv == 2){
        texture = irrlicht.driver->getTexture("media/textures/npc3.png"); 
        irrlicht.driver->makeColorKeyTexture(texture, SColor(255,255,255,255));
    }

    if(idConv == 3){
        texture = irrlicht.driver->getTexture("media/textures/npc4.png");
        irrlicht.driver->makeColorKeyTexture(texture, SColor(255,255,255,255));
    }

    if(idConv == 4){
        texture = irrlicht.driver->getTexture("media/textures/npc5.png");
        irrlicht.driver->makeColorKeyTexture(texture, SColor(255,255,255,255));
    }

    if(idConv == 5){
        texture = irrlicht.driver->getTexture("media/textures/npc6.png");
        irrlicht.driver->makeColorKeyTexture(texture, SColor(255,255,255,255));
    }

    if(idConv == 6){
        texture = irrlicht.driver->getTexture("media/textures/npc7.png");
        irrlicht.driver->makeColorKeyTexture(texture, SColor(255,255,255,255));
    }

    //if(vida == 0){
    //    //TODO: clock que deje unos segundos antes de reiniciar nivel
    //    texture = irrlicht.driver->getTexture("media/textures/vida0.png");
    //    irrlicht.driver->makeColorKeyTexture(texture, SColor(255,255,255,255));
    //}

    if(texture)
        conver->setImage(texture); 
        //irrlicht.driver->draw2DImage(texture, vector2di(623, 113));

    conver->setVisible(true);
    stam->setVisible(false);
    lifeContainer->setVisible(false);

    if(key)
        key->setVisible(false);

    if(orb)
        orb->setVisible(false);
}


void FacadeIrrRender::clearConver(){
    conver->setVisible(false);
    stam->setVisible(true);
    lifeContainer->setVisible(true);

    if(key)
        key->setVisible(true);

    if(orb)
        orb->setVisible(true);
}


void FacadeIrrRender::drawStealthBar(int disc) {
  
        video::ITexture* texture = nullptr;

    if(disc == 1){
        texture = irrlicht.driver->getTexture("media/textures/barraSigilo1.png");
        irrlicht.driver->makeColorKeyTexture(texture, SColor(255,255,255,255));
    }

    if(disc == 2){
        texture = irrlicht.driver->getTexture("media/textures/barraSigilo2.png"); 
        irrlicht.driver->makeColorKeyTexture(texture, SColor(255,255,255,255));
    }

    if(disc == 3){
        texture = irrlicht.driver->getTexture("media/textures/barraSigilo3.png");
        irrlicht.driver->makeColorKeyTexture(texture, SColor(255,255,255,255));
    }

    if(disc == 4){
        texture = irrlicht.driver->getTexture("media/textures/barraSigilo4.png");
        irrlicht.driver->makeColorKeyTexture(texture, SColor(255,255,255,255));
    }

    if(disc == 5){
        texture = irrlicht.driver->getTexture("media/textures/barraSigiloFull.png");
        irrlicht.driver->makeColorKeyTexture(texture, SColor(255,255,255,255));
    }


    //if(vida == 0){
    //    //TODO: clock que deje unos segundos antes de reiniciar nivel
    //    texture = irrlicht.driver->getTexture("media/textures/vida0.png");
    //    irrlicht.driver->makeColorKeyTexture(texture, SColor(255,255,255,255));
    //}

    if(texture)
        barStealth->setImage(texture); 
        //irrlicht.driver->draw2DImage(texture, vector2di(623, 113));

}

void FacadeIrrRender::drawSeen(bool seen){
    video::ITexture* texture = irrlicht.driver->getTexture("media/textures/unseen.png"); 
    if(seen){
        texture = irrlicht.driver->getTexture("media/textures/seen.png"); 
    }
    
    eye->setImage(texture); 
    
}

/* --- HUD STAMINA --- */

void FacadeIrrRender::initStam(){
    stam = irrlicht.guienv->addImage(core::rect<s32>(0, 720-300, 300, 720 - 50));
    video::ITexture* texture = irrlicht.driver->getTexture("media/textures/stam3.png"); 
    irrlicht.driver->getTexture("media/textures/stam2.png"); 
    irrlicht.driver->getTexture("media/textures/stam1.png"); 
    irrlicht.driver->getTexture("media/textures/stam0.png"); 
    stam->setImage(texture);
}   

void FacadeIrrRender::drawStam(const ARCS::Entity &player){
    if(player.inp){
        video::ITexture* texture = nullptr;
        float stamPlayer = player.inp->stamina;

        if(stamPlayer >= 1.2){ //66%
            texture = irrlicht.driver->getTexture("media/textures/stam3.png"); 
            irrlicht.driver->makeColorKeyTexture(texture, SColor(255, 255, 255, 255));
        }

        if(stamPlayer < 1.2 && stamPlayer >= 0.6){ //33%
            texture = irrlicht.driver->getTexture("media/textures/stam2.png");
            irrlicht.driver->makeColorKeyTexture(texture, SColor(255, 255, 255, 255));
        }

        if(stamPlayer < 0.6 && stamPlayer > 0){
            texture = irrlicht.driver->getTexture("media/textures/stam1.png"); 
            irrlicht.driver->makeColorKeyTexture(texture, SColor(255, 255, 255, 255));
        }

        if(stamPlayer <= 0){
            texture = irrlicht.driver->getTexture("media/textures/stam0.png"); 
            irrlicht.driver->makeColorKeyTexture(texture, SColor(255, 255, 255, 255));
        }

        if(texture)
            stam->setImage(texture); 
    }
}

/* --- DEATH --- */

void FacadeIrrRender::drawHudDeath() {
    if(!death)
        death = irrlicht.guienv->addImage(core::rect<s32>(0, 720-250, 300, 720));

    death->setVisible(true);
    video::ITexture* texture = nullptr;
    texture = irrlicht.driver->getTexture("media/textures/vida0.png");
    death->setImage(texture);
}

void FacadeIrrRender::clearHudDeath() {
    death->setVisible(false);
}

/* --- INVENTARY: KEY --- */

void FacadeIrrRender::keyHUD(int id) {
    if(!key)
        key = irrlicht.guienv->addImage(core::rect<s32>(0, 720-250, 300, 720)); //xy    x2y
                                                                                        //xy2   x2y2
    key->setVisible(true);
    video::ITexture* texture = nullptr;

    if(id == 0) //Key gris del nivel, por ejemplo
        texture = irrlicht.driver->getTexture("media/textures/yesKeyGris.png");
    if(id == 1) //Key azul
        texture = irrlicht.driver->getTexture("media/textures/yesKeyAzul.png");
    if(id == 2) //Key lila
        texture = irrlicht.driver->getTexture("media/textures/yesKeyLila.png");
    if(id == 3) //Key blanca
        texture = irrlicht.driver->getTexture("media/textures/yesKeyBlanca.png");

    key->setImage(texture);
}

void FacadeIrrRender::clearKeyHUD(int id){
    if(!key)
        key = irrlicht.guienv->addImage(core::rect<s32>(0, 720-250, 300, 720)); //xy    x2y
                                                                                        //xy2   x2y2
    key->setVisible(true);
    video::ITexture* texture = nullptr;
    
    if(id == 0) //Key gris del nivel, por ejemplo
        texture = irrlicht.driver->getTexture("media/textures/noKeyGris.png");
    if(id == 1) //Key azul
        texture = irrlicht.driver->getTexture("media/textures/noKeyAzul.png");
    if(id == 2) //Key lila
        texture = irrlicht.driver->getTexture("media/textures/noKeyLila.png");
    if(id == 3) //Key blanca
        texture = irrlicht.driver->getTexture("media/textures/noKeyBlanca.png");

    key->setImage(texture);
}

/* --- INVENTARY: ORB --- */

void FacadeIrrRender::orbHUD() {
    if(!orb)
        orb = irrlicht.guienv->addImage(core::rect<s32>(0, 720-250, 300, 720));

    orb->setVisible(true);
    video::ITexture* texture = nullptr;
    texture = irrlicht.driver->getTexture("media/textures/yesOrb.png");
    orb->setImage(texture);
}

/* --- TEXT KEY --- */

void FacadeIrrRender::textKey(int id){
    if(!textKeyPick)
        textKeyPick = irrlicht.guienv->addImage(core::rect<s32>(0, 720-720, 1280, 720));

    textKeyPick->setVisible(true);
    video::ITexture* texture = nullptr;

    if(id == 0)
        texture = irrlicht.driver->getTexture("media/textures/keyCarcel.png"); 
    
    if(id == 1)
        texture = irrlicht.driver->getTexture("media/textures/keyBosque.png");
    
    if(id == 2)
        texture = irrlicht.driver->getTexture("media/textures/keyFortaleza.png");

    textKeyPick->setImage(texture);
}

void FacadeIrrRender::clearTextKey(int id){
    if(textKeyPick)
        textKeyPick->setVisible(false);
}   

/* --- TEXT ORB --- */

void FacadeIrrRender::textOrb(){
    if(!textOrbPick)
        textOrbPick = irrlicht.guienv->addImage(core::rect<s32>(0, 720-720, 1280, 720));

    textOrbPick->setVisible(true);
    video::ITexture* texture = nullptr;
    texture = irrlicht.driver->getTexture("media/textures/cogerOrb.png"); 
    textOrbPick->setImage(texture);
}

void FacadeIrrRender::clearTextOrb(){
    if(textOrbPick)
        textOrbPick->setVisible(false); //TODO: no borra el orbe
}   

/* --- BAJA SIGILOSA KILL--- */

void FacadeIrrRender::drawKill() {
    if(!kill)
        kill = irrlicht.guienv->addImage(core::rect<s32>(600, 670, 680, 710));

    kill->setVisible(true);
    video::ITexture* texture = nullptr;
    texture = irrlicht.driver->getTexture("media/textures/kill.png"); 
    kill->setImage(texture);
}

void FacadeIrrRender::clearKill() {
    if(kill)
        kill->setVisible(false);
}

void FacadeIrrRender::setSkybox(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back){

}


void FacadeIrrRender::setWindowTitle(std::string_view&& title) {
    
}

void FacadeIrrRender::addSceneDirectionalNodeLight(glm::vec3, glm::vec3, glm::vec3, glm::vec3, bool){}
void FacadeIrrRender::addScenePointNodeLight(glm::vec3, float, float, float, glm::vec3, glm::vec3, glm::vec3, bool){}
void FacadeIrrRender::addSceneSpotNodeLight(glm::vec3, glm::vec3, float, float, float, glm::vec3, glm::vec3, glm::vec3, float, float, bool){}
void FacadeIrrRender::deleteLights(){}