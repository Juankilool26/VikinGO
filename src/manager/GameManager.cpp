#include "GameManager.hpp"
#include <components/ID.hpp>



namespace ARCS {






Level::Level(ARCS::StateManager& sm, int& l, std::string_view s, ARCS::RenderSystem& rs, bool restart)
    :   SM{ sm }
    ,   lvl { l }
    ,   player { GOFact.loadLevelJSON(s, l,entity_man.getMapComponent()) }
    ,   render_sys { rs }
{
    if(!restart){
        ManFacadeRender::GetInstance()->getFacade()->paintChargeScreen();
    }   
    std::vector<std::string> faces;
    faces.reserve(6);

    faces.push_back("media/skybox/right.jpg");
    faces.push_back("media/skybox/left.jpg");
    faces.push_back("media/skybox/top.jpg");
    faces.push_back("media/skybox/bottom.jpg");
    faces.push_back("media/skybox/front.jpg");
    faces.push_back("media/skybox/back.jpg");

    glm::vec3 dir = glm::vec3(-0.2f, -1.0f, -0.3f);
    glm::vec3 amb = glm::vec3(0.05f, 0.05f, 0.05f);
    glm::vec3 diff = glm::vec3(0.4f, 0.4f, 0.4f);
    glm::vec3 spec = glm::vec3(0.5f, 0.5f, 0.5f);
    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;
    //1.8017

    glm::vec3 pointLightLevel0[5] = {
        glm::vec3( -15.921f,  0.6f,  -2.79114f),
        glm::vec3( -16.102f,   1.9473f,  -0.44395f),
        glm::vec3( -16.641f,   0.81122f, -0.44395f),
        glm::vec3( -16.641f,  -3.9191f,  -0.44395f),
        glm::vec3( -16.102f,  -5.0547f,  -0.44395f)
    };

    /* glm::vec3 pointLightLevel1[8] = {
        glm::vec3( 13.239f, -1.2508f, -4.6907f),
        glm::vec3( 26.475f,  4.1258f, -4.6907f),
        glm::vec3( 31.721f,  5.1153f, -4.6907f),
        glm::vec3( 31.721f, -6.7209f, -4.6907f),
        glm::vec3( 31.889f, -12.191f, -4.6907f),
        glm::vec3( 53.489f, -20.107f, -4.6907f),
        glm::vec3( 43.828f,  -6.563f, -4.6907f),
        glm::vec3( 43.828f,  4.9807f, -4.6907f)
        //glm::vec3( 66.802f,  4.9807f, -4.6907f),
        //glm::vec3( 66.802f, -13.186f, -4.6907f),
        //glm::vec3( 66.589f, -13.186f, -4.6907f),
        //glm::vec3( 77.646f,  10.343f, -1.5233f),
        //glm::vec3( 77.646f, -19.725f, -1.5233f),
        //glm::vec3( 92.405f, -19.725f, -1.5233f),
        //glm::vec3( 72.286f, -7.051f, -4.6907f),
        //glm::vec3( 72.286f, -2.4136f, -4.6907f),
        //glm::vec3( 81.926f, -12.419f, -4.6907f),
        //glm::vec3( 96.714f, -12.419f, -4.6907f),
        //glm::vec3( 82.327f, 2.9907f, -4.6907f),
        //glm::vec3( 104.42f, -7.051f, -4.6907f),
        //glm::vec3( 104.42f, -2.3406f, -4.6907f),
        //glm::vec3( 110.02f, -11.068f, -4.6907f),
        //glm::vec3( 103.51f, 2.9176f, -4.6907f),
        //glm::vec3( 103.51f, 37.498f, -4.6907f),
        //glm::vec3( 71.044f, 27.821f, -4.6907f)
    }; */

    glm::vec3 pointLightLevel2[8] = {
        glm::vec3(  -45.73f,   17.984f,  -3.1137f),
        glm::vec3(  -27.301f, -34.189f,  -0.58064f),
        glm::vec3(   14.309f, -41.067f,  -3.6095f),
        glm::vec3(   42.131f, -43.676f,  -0.7934f),
        glm::vec3(   53.341f,  34.58f,   -3.1137f),
        glm::vec3(   36.063f,  47.478f,  -3.1137f),
        glm::vec3(   28.913f,  37.379f,  -3.1137f),
        glm::vec3(   47.307f,  52.558f,  -4.5182f)
    };

    glm::vec3 pointLightLevel3[8] = {
        glm::vec3(  77.036f,   115.85f,  -7.1763f),
        glm::vec3(  77.036f,   105.38f,  -7.1763f),
        glm::vec3(  77.036f,   95.806f,  -7.1763f),
        glm::vec3(  47.119f,   97.843f,  -7.1763f),
        glm::vec3(  47.119f,   104.9f,  -7.1763f),
        glm::vec3(  47.119f,   115.01f,  -7.1763f),
        glm::vec3(  40.129f,   38.799f,  -7.1763f),
        glm::vec3(  -38.6f,   59.958f,  -6.8929f)
        //glm::vec3(  -38.6f,   64.366f,  -6.8929f),
        //glm::vec3(  -38.6f,   83.291f,  -6.8929f),
        //glm::vec3(  -68.664f,   83.291f,  -6.8929f),
        //glm::vec3(  -68.664f,   64.474f,  -6.8929f),
        //glm::vec3(  -68.664f,   59.986f,  -6.8929f),
        //glm::vec3(  -68.664f,   41.494f,  -6.8929f)
    };
/* 
    glm::vec3 pointLightLevel4[8] = {
        glm::vec3( -6.5f,  -79.138f,  0.46945f),
        glm::vec3( -5.5f,  -81.31f,  0.44395f),
        glm::vec3( -6.6f,  -82.637f,  0.44395f),
        glm::vec3( -6.6f,  -84.748f,  0.44395f),
        glm::vec3( -5.7f,  -86.87f,  0.44395f),
        glm::vec3( -5.7f,  -88.451f,  0.44395f),
        glm::vec3( 6.2f,  -78.366f,  0.44395f),
        glm::vec3( 7.1f,  -81.33f,  0.44395f)
        //glm::vec3( 5.9f,  -83.428f,  0.44395f),
        //glm::vec3( 5.9f,  -85.666f,  0.44395f),
        //glm::vec3( 7.1f,  -87.767f,  0.44395f),
        //glm::vec3( 7.1f,  -90.578f,  0.44395f)
    }; */

/*
    glm::vec3 pointLightLevel0[5] = {
        glm::vec3( -15.921f,  0.6f,  -2.79114f),
        glm::vec3( -16.102f,   1.9473f,  0.44395f),
        glm::vec3( -16.641f,   0.81122f, 0.44395f),
        glm::vec3( -16.641f,  -3.9191f,  0.44395f),
        glm::vec3( -16.102f,  -5.0547f,  0.44395f)
    };

    glm::vec3 pointLightLevel2[8] = {
        glm::vec3(  -45.73f,   17.984f,  3.1137f),
        glm::vec3(  -27.301f, -34.189f,  0.58064f),
        glm::vec3(   14.309f, -41.067f,  3.6095f),
        glm::vec3(   42.131f, -43.676f,  0.7934f),
        glm::vec3(   53.341f,  34.58f,   3.1137f),
        glm::vec3(   36.063f,  47.478f,  3.1137f),
        glm::vec3(   28.913f,  37.379f,  3.1137f),
        glm::vec3(   47.307f,  52.558f,  4.5182f)
    };
*/
   
    
    ManFacadeRender::GetInstance()->getFacade()->drawStealthBar(0);
    ManFacadeRender::GetInstance()->getFacade()->drawHud(player);

    /*                      LEVEL 0 TUTORIAL                        */

    if(lvl == 0) {
        ManFacadeRender::GetInstance()->getFacade()->deleteLights();
        ManFacadeRender::GetInstance()->getFacade()->addSceneDirectionalNodeLight(dir, amb, diff, spec, true);
        ManFacadeRender::GetInstance()->getFacade()->addScenePointNodeLight(pointLightLevel0[0],constant,linear,quadratic,amb,diff,spec,true);
        ManFacadeRender::GetInstance()->getFacade()->addScenePointNodeLight(pointLightLevel0[1],constant,linear,quadratic,amb,diff,spec,true);
        ManFacadeRender::GetInstance()->getFacade()->addScenePointNodeLight(pointLightLevel0[2],constant,linear,quadratic,amb,diff,spec,true);
        ManFacadeRender::GetInstance()->getFacade()->addScenePointNodeLight(pointLightLevel0[3],constant,linear,quadratic,amb,diff,spec,true);
        ManFacadeRender::GetInstance()->getFacade()->addScenePointNodeLight(pointLightLevel0[4],constant,linear,quadratic,amb,diff,spec,true);

        ManFacadeSound::GetInstance()->getFacade()->startEvent(KeySound::Ambientes_forest_2);
        ManFacadeRender::GetInstance()->getFacade()->setSkybox("media/skybox/right.bmp","media/skybox/left.bmp","media/skybox/top.bmp","media/skybox/bottom.bmp","media/skybox/front.bmp","media/skybox/back.bmp");
        //ManFacadeRender::GetInstance()->getFacade()->sm addSceneDirectionalNodeLight(dir,amb,diff,spec,true);

        auto& npc = GOFact.createObject(glm::vec3(-8.1525,1.6109,-14.634), glm::vec3(0,0,0), "media/models/personajeBase.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        trigger_sto.RegisterConversation(npc,trigger_sys, KeySound::Voces_NPC_attackTrainer, 0);

        auto& npc2 = GOFact.createObject(glm::vec3(5.8321,1.6109,-5.4123), glm::vec3(0,0,0), "media/models/personajeBase.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        trigger_sto.RegisterConversation(npc2,trigger_sys, KeySound::Voces_NPC_stealthTrainer, 1);
        
        auto& npc3 = GOFact.createObject(glm::vec3(15.868,1.6109,8.7049), glm::vec3(0,0,0), "media/models/personajeBase.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        trigger_sto.RegisterConversation(npc3,trigger_sys, KeySound::Voces_NPC_speedTrainer, 2);

        auto& orb = GOFact.createObject(glm::vec3(-16.214,1.35,13.585), glm::vec3(0,0,0), "media/models/orbePasoDeNivel.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(orb);
        sensoryMemory.registEnt2React(GOFact.createObject(glm::vec3(-16.762,2.2515,1.5625), glm::vec3(0,0,0), "media/models/auraPasoNivel.obj", glm::vec3(-0.5,-1.700,-0.5),glm::vec3(0.5,2,0.5)));

        //auto& trap = GOFact.createObject(glm::vec3(-7.214,1.35,7.585), glm::vec3(0,0,0), "media/models/trampaOso.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        //sensoryMemory.registEnt2React(trap);
        //trigger_sto.RegisterTrap(trap,trigger_sys);
        
        trigger_sto.RegisterActivator(npc3,trigger_sys,trigger_sto.RegisterOrb(orb,trigger_sys));

        finalPos = glm::vec3(-18.718,2,1.5774);
    }

    /*                LEVEL 1 TUTORIAL INTERMEDIO                  */
    
    else if(lvl == 1) {
        ManFacadeRender::GetInstance()->getFacade()->deleteLights();
        ManFacadeRender::GetInstance()->getFacade()->addSceneDirectionalNodeLight(dir, amb, diff, spec, true);
        ManFacadeRender::GetInstance()->getFacade()->hudInit();
        ManFacadeSound::GetInstance()->getFacade()->startEvent(KeySound::Ambientes_forest_2);
        ManFacadeRender::GetInstance()->getFacade()->setSkybox("media/skybox/right.bmp","media/skybox/left.bmp","media/skybox/top.bmp","media/skybox/bottom.bmp","media/skybox/front.bmp","media/skybox/back.bmp");

        //KEYs 1a part
        auto& key = GOFact.createObject(glm::vec3(18.497,1.35, -29.977), glm::vec3(0,0,0), "media/models/llave2.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(key);
        sensoryMemory.registEnt2React(GOFact.createObject(glm::vec3(13.408,2.05,-6.3967), glm::vec3(0,180,0), "media/models/puertaCelda.obj", glm::vec3(-0.5,-1.700,-0.5),glm::vec3(0.5,2,0.5)));
        trigger_sto.RegisterKey(key,trigger_sys, 0); // Key gris


        //BEERs all parts
        auto& beer = GOFact.createObject(glm::vec3(-150.29,1.35,-6.1573), glm::vec3(0,0,0), "media/models/hidromiel.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(beer);
        trigger_sto.RegisterBeer(beer,trigger_sys);

        auto& beer2 = GOFact.createObject(glm::vec3(-83.896,1.35,-6.1573), glm::vec3(0,0,0), "media/models/hidromiel.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(beer2);
        trigger_sto.RegisterBeer(beer2,trigger_sys);

        auto& beer3 = GOFact.createObject(glm::vec3(-6.7109,1.35,-6.1573), glm::vec3(0,0,0), "media/models/hidromiel.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(beer3);
        trigger_sto.RegisterBeer(beer3,trigger_sys);


        //TRAPs 1a part
        auto& trap = GOFact.createObject(glm::vec3(36.86,0.090009,-12.847), glm::vec3(0,0,0), "media/models/trampaOso.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(trap);
        trigger_sto.RegisterTrap(trap,trigger_sys);

        auto& trap2 = GOFact.createObject(glm::vec3(30.82,0.090009,-22.794), glm::vec3(0,0,0), "media/models/trampaOso.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(trap2);
        trigger_sto.RegisterTrap(trap2,trigger_sys);

        auto& trap3 = GOFact.createObject(glm::vec3(20.935,0.090009,-12.847), glm::vec3(0,0,0), "media/models/trampaOso.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(trap3);
        trigger_sto.RegisterTrap(trap3,trigger_sys);

        auto& trap4 = GOFact.createObject(glm::vec3(16.586,0.090009,-20.817), glm::vec3(0,0,0), "media/models/trampaOso.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(trap4);
        trigger_sto.RegisterTrap(trap4,trigger_sys);

        auto& trap5 = GOFact.createObject(glm::vec3(22.253,0.090009,-12.382), glm::vec3(0,0,0), "media/models/trampaOso.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(trap5);
        trigger_sto.RegisterTrap(trap5,trigger_sys);

        auto& trap6 = GOFact.createObject(glm::vec3(15.553,0.090009,-0.12521), glm::vec3(0,0,0), "media/models/trampaOso.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(trap6);
        trigger_sto.RegisterTrap(trap6,trigger_sys);

        auto& trap7 = GOFact.createObject(glm::vec3(23.077,0.090009,6.2449), glm::vec3(0,0,0), "media/models/trampaOso.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(trap7);
        trigger_sto.RegisterTrap(trap7,trigger_sys);

        auto& trap8 = GOFact.createObject(glm::vec3(35.762,0.090009,11.407), glm::vec3(0,0,0), "media/models/trampaOso.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(trap8);
        trigger_sto.RegisterTrap(trap8,trigger_sys);

        auto& trap9 = GOFact.createObject(glm::vec3(25.822,0.090009,9.4483), glm::vec3(0,0,0), "media/models/trampaOso.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(trap9);
        trigger_sto.RegisterTrap(trap9,trigger_sys);

        auto& trap10 = GOFact.createObject(glm::vec3(16.157,0.090009,9.8693), glm::vec3(0,0,0), "media/models/trampaOso.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(trap10);
        trigger_sto.RegisterTrap(trap10,trigger_sys);

        auto& trap11 = GOFact.createObject(glm::vec3(22.088,0.090009,19.534), glm::vec3(0,0,0), "media/models/trampaOso.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(trap11);
        trigger_sto.RegisterTrap(trap11,trigger_sys);

        auto& trap12 = GOFact.createObject(glm::vec3(11.874,0.090009,17.722), glm::vec3(0,0,0), "media/models/trampaOso.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(trap12);
        trigger_sto.RegisterTrap(trap12,trigger_sys);

        //KEYs 2a part
        auto& key2 = GOFact.createObject(glm::vec3(-45.929,1.35, -6.2263), glm::vec3(0,0,0), "media/models/llave.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(key2);
        sensoryMemory.registEnt2React(GOFact.createObject(glm::vec3(-77.169,2.05,-6.3967), glm::vec3(0,180,0), "media/models/puertaCelda2.obj", glm::vec3(-0.5,-1.700,-0.5),glm::vec3(0.5,2,0.5)));
        trigger_sto.RegisterKey(key2,trigger_sys, 0); // Key gris

        //TRAPs 2a part
        auto& trap13 = GOFact.createObject(glm::vec3(-24.183,0.090009,-8.7963), glm::vec3(0,0,0), "media/models/trampaOso.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(trap13);
        trigger_sto.RegisterTrap(trap13,trigger_sys);

        auto& trap14 = GOFact.createObject(glm::vec3(-29.586,0.090009,-14.002), glm::vec3(0,0,0), "media/models/trampaOso.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(trap14);
        trigger_sto.RegisterTrap(trap14,trigger_sys);

        auto& trap15 = GOFact.createObject(glm::vec3(-30.179,0.090009,-1.7452), glm::vec3(0,0,0), "media/models/trampaOso.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(trap15);
        trigger_sto.RegisterTrap(trap15,trigger_sys);

        auto& trap16 = GOFact.createObject(glm::vec3(-23.458,0.090009,1.945), glm::vec3(0,0,0), "media/models/trampaOso.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(trap16);
        trigger_sto.RegisterTrap(trap16,trigger_sys);

        auto& trap17 = GOFact.createObject(glm::vec3(-36.11,0.090009,4.1197), glm::vec3(0,0,0), "media/models/trampaOso.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(trap17);
        trigger_sto.RegisterTrap(trap17,trigger_sys);

        auto& trap18 = GOFact.createObject(glm::vec3(-36.967,0.090009,-7.083), glm::vec3(0,0,0), "media/models/trampaOso.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(trap18);
        trigger_sto.RegisterTrap(trap18,trigger_sys);

        auto& trap19 = GOFact.createObject(glm::vec3(-41.184,0.090009,-13.805), glm::vec3(0,0,0), "media/models/trampaOso.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(trap19);
        trigger_sto.RegisterTrap(trap19,trigger_sys);

        auto& trap20 = GOFact.createObject(glm::vec3(-53.507,0.090009,-11.235), glm::vec3(0,0,0), "media/models/trampaOso.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(trap20);
        trigger_sto.RegisterTrap(trap20,trigger_sys);

        auto& trap21 = GOFact.createObject(glm::vec3(-63.326,0.090009,-13.08), glm::vec3(0,0,0), "media/models/trampaOso.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(trap21);
        trigger_sto.RegisterTrap(trap21,trigger_sys);

        auto& trap22 = GOFact.createObject(glm::vec3(-55.748,0.090009,0.42939), glm::vec3(0,0,0), "media/models/trampaOso.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(trap22);
        trigger_sto.RegisterTrap(trap22,trigger_sys);

        auto& trap23 = GOFact.createObject(glm::vec3(-46.654,0.090009,3.5266), glm::vec3(0,0,0), "media/models/trampaOso.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(trap23);
        trigger_sto.RegisterTrap(trap23,trigger_sys);

        auto& trap24 = GOFact.createObject(glm::vec3(-64.38,0.090009,5.3037), glm::vec3(0,0,0), "media/models/trampaOso.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(trap24);
        trigger_sto.RegisterTrap(trap24,trigger_sys);

        auto& trap25 = GOFact.createObject(glm::vec3(-71.036,0.090009,-10.707), glm::vec3(0,0,0), "media/models/trampaOso.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(trap25);
        trigger_sto.RegisterTrap(trap25,trigger_sys);

        auto& trap26 = GOFact.createObject(glm::vec3(-66.16,0.090009,4.4492), glm::vec3(0,0,0), "media/models/trampaOso.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(trap26);
        trigger_sto.RegisterTrap(trap26,trigger_sys);

        //KEYs 3a part
        auto& key3 = GOFact.createObject(glm::vec3(-132.27,1.35, -20.133), glm::vec3(0,0,0), "media/models/llave3.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(key3);
        sensoryMemory.registEnt2React(GOFact.createObject(glm::vec3(-143.75,2.05,-6.3967), glm::vec3(0,180,0), "media/models/puertaCelda3.obj", glm::vec3(-0.5,-1.700,-0.5),glm::vec3(0.5,2,0.5)));
        trigger_sto.RegisterKey(key3,trigger_sys, 0); // Key gris

        finalPos = glm::vec3(-157.36, 1.1, -6.2838);
    }
    

    /*                      LEVEL 2 CARCEL                        */
    
    
    else if (lvl == 2) {

        ManFacadeRender::GetInstance()->getFacade()->hudInit();
        ManFacadeSound::GetInstance()->getFacade()->startEvent(KeySound::Musica_Level);
        //ManFacadeRender::GetInstance()->getFacade()->clearKeyHUD();
        ManFacadeRender::GetInstance()->getFacade()->setSkybox("media/skybox/right.bmp","media/skybox/left.bmp","media/skybox/top.bmp","media/skybox/bottom.bmp","media/skybox/front.bmp","media/skybox/back.bmp");
        ManFacadeRender::GetInstance()->getFacade()->deleteLights();
        ManFacadeRender::GetInstance()->getFacade()->addSceneDirectionalNodeLight(dir, amb, diff, spec, true);
        ManFacadeRender::GetInstance()->getFacade()->addScenePointNodeLight(pointLightLevel2[0],constant,linear,quadratic,amb,diff,spec,true);
        ManFacadeRender::GetInstance()->getFacade()->addScenePointNodeLight(pointLightLevel2[1],constant,linear,quadratic,amb,diff,spec,true);
        ManFacadeRender::GetInstance()->getFacade()->addScenePointNodeLight(pointLightLevel2[2],constant,linear,quadratic,amb,diff,spec,true);
        ManFacadeRender::GetInstance()->getFacade()->addScenePointNodeLight(pointLightLevel2[3],constant,linear,quadratic,amb,diff,spec,true);
        ManFacadeRender::GetInstance()->getFacade()->addScenePointNodeLight(pointLightLevel2[4],constant,linear,quadratic,amb,diff,spec,true);
        ManFacadeRender::GetInstance()->getFacade()->addScenePointNodeLight(pointLightLevel2[5],constant,linear,quadratic,amb,diff,spec,true);
        ManFacadeRender::GetInstance()->getFacade()->addScenePointNodeLight(pointLightLevel2[6],constant,linear,quadratic,amb,diff,spec,true);
        ManFacadeRender::GetInstance()->getFacade()->addScenePointNodeLight(pointLightLevel2[7],constant,linear,quadratic,amb,diff,spec,true);

        auto& key = GOFact.createObject(glm::vec3(21.157,0.9537,-14.217), glm::vec3(0,0,0), "media/models/llave.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(key);
        sensoryMemory.registEnt2React(GOFact.createObject(glm::vec3(28.885,2.4042,-1.4466),glm::vec3(0,0,0), "media/models/puertaCelda.obj", glm::vec3(-0.150,-1.700,-1.350),glm::vec3(0.150,1.700,1.350)));
        trigger_sto.RegisterKey(key,trigger_sys, 0); // Key gris
        
        /* auto& key = GOFact.createObject(glm::vec3(21.157,0.9537,-14.217), glm::vec3(0,0,0), "media/models/llave.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        GOFact.createObject(glm::vec3(28.885,2.4042,-1.4466), glm::vec3(0,0,0), "media/models/puertaCelda.obj", glm::vec3(-0.150,-1.700,-1.350),glm::vec3(0.150,1.700,1.350));
        trigger_sto.RegisterKey(key,trigger_sys); */

        auto& palanca = GOFact.createObject(glm::vec3(112.63,0.9537,9.6967), glm::vec3(0,0,0), "media/models/palanca.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(GOFact.createObject(glm::vec3(100.43,3.1794,0.30263), glm::vec3(0,180,0), "media/models/puerta.obj",glm::vec3(-1.5, -1.5, -0.6),glm::vec3(1.5, 1.5, 0.6)));
        trigger_sto.RegisterLever(palanca,trigger_sys);

        auto& npc = GOFact.createObject(glm::vec3(20.39,1.4,4.8251), glm::vec3(0,180,0), "media/models/pariaMasculinoSentado.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        trigger_sto.RegisterConversation(npc,trigger_sys, KeySound::Voces_NPC_prisoner, 3);
        /* auto& npc = GOFact.createObject(glm::vec3(20.39,2,7.0251), glm::vec3(0,0,0), "media/models/media/models/personajeBase.obj.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        trigger_sto.RegisterConversation(npc,trigger_sys,"event:/Voces/Femeninas/Patroller_women",""); */

        auto& beer = GOFact.createObject(glm::vec3(100.51,1.35,-3.1312), glm::vec3(0,0,0), "media/models/hidromiel.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(beer);
        trigger_sto.RegisterBeer(beer,trigger_sys);

        auto& orb = GOFact.createObject(glm::vec3(42.63,1.35,15.93), glm::vec3(0,0,0), "media/models/orbePasoDeNivel.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(orb);
        sensoryMemory.registEnt2React(GOFact.createObject(glm::vec3(54.969,2.6212,-33.457), glm::vec3(0,0,0), "media/models/auraPasoNivel.obj", glm::vec3(-0.5,-1.700,-0.5),glm::vec3(0.5,2,0.5)));
        trigger_sto.RegisterOrb(orb,trigger_sys);

        finalPos = glm::vec3(54.692, 2, -33.437);
    }

    /*                      LEVEL 3 BOSQUE                        */

    else if(lvl == 3) {
        ManFacadeRender::GetInstance()->getFacade()->hudInit();
        ManFacadeSound::GetInstance()->getFacade()->startEvent(KeySound::Ambientes_forest_2);
        //ManFacadeRender::GetInstance()->getFacade()->clearKeyHUD();
        ManFacadeRender::GetInstance()->getFacade()->setSkybox("media/skybox/right.bmp","media/skybox/left.bmp","media/skybox/top.bmp","media/skybox/bottom.bmp","media/skybox/front.bmp","media/skybox/back.bmp");

        ManFacadeRender::GetInstance()->getFacade()->deleteLights();
        ManFacadeRender::GetInstance()->getFacade()->addSceneDirectionalNodeLight(dir, amb, diff, spec, true);
        ManFacadeRender::GetInstance()->getFacade()->addScenePointNodeLight(pointLightLevel3[0],constant,linear,quadratic,amb,diff,spec,true);
        ManFacadeRender::GetInstance()->getFacade()->addScenePointNodeLight(pointLightLevel3[1],constant,linear,quadratic,amb,diff,spec,true);
        ManFacadeRender::GetInstance()->getFacade()->addScenePointNodeLight(pointLightLevel3[2],constant,linear,quadratic,amb,diff,spec,true);
        ManFacadeRender::GetInstance()->getFacade()->addScenePointNodeLight(pointLightLevel3[3],constant,linear,quadratic,amb,diff,spec,true);
        ManFacadeRender::GetInstance()->getFacade()->addScenePointNodeLight(pointLightLevel3[4],constant,linear,quadratic,amb,diff,spec,true);
        ManFacadeRender::GetInstance()->getFacade()->addScenePointNodeLight(pointLightLevel3[5],constant,linear,quadratic,amb,diff,spec,true);
        ManFacadeRender::GetInstance()->getFacade()->addScenePointNodeLight(pointLightLevel3[6],constant,linear,quadratic,amb,diff,spec,true);
        ManFacadeRender::GetInstance()->getFacade()->addScenePointNodeLight(pointLightLevel3[7],constant,linear,quadratic,amb,diff,spec,true);

        auto& key = GOFact.createObject(glm::vec3(53.372,0.9537,15.0), glm::vec3(0,0,0), "media/models/llave.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(key);
        sensoryMemory.registEnt2React(GOFact.createObject(glm::vec3(37.158,1.6,-3.4449), glm::vec3(0,0,0), "media/models/puertaValla.obj", glm::vec3(-3.0,-1.700,-1.350),glm::vec3(3.0,1.700,1.350)));
        trigger_sto.RegisterKey(key,trigger_sys, 0); // Key gris
        
        /*  auto& key = GOFact.createObject(glm::vec3(53.372,0.9537,15.0), glm::vec3(0,0,0), "media/models/llave.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        GOFact.createObject(glm::vec3(37.158,1.6,-3.4449), glm::vec3(0,0,0),glm::vec3(0,0,0), "media/models/puertaValla.obj", glm::vec3(-0.150,-1.700,-1.350),glm::vec3(0.150,1.700,1.350));
        trigger_sto.RegisterKey(key,trigger_sys); */

        auto& orb = GOFact.createObject(glm::vec3(41.937,1.35,43.6), glm::vec3(0,0,0), "media/models/orbePasoDeNivel.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(orb);
        sensoryMemory.registEnt2React(GOFact.createObject(glm::vec3(47.397,2.2,-52.927), glm::vec3(0,90,0), "media/models/auraPasoNivel.obj", glm::vec3(-0.5,-1.700,-0.5),glm::vec3(0.5,2,0.5)));
        trigger_sto.RegisterOrb(orb,trigger_sys);

        auto& palanca = GOFact.createObject(glm::vec3(-27.163,0.9537,34.521), glm::vec3(0,90,0), "media/models/palanca.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(GOFact.createObject(glm::vec3(4.2298,3.1794,-25.279), glm::vec3(0,180,0), "media/models/tablaPuenteAlta.obj",glm::vec3(-3.5, -1.5, -0.6),glm::vec3(3.5, 1.5, 0.5)));
        trigger_sto.RegisterLever(palanca,trigger_sys);

        auto& npc = GOFact.createObject(glm::vec3(-39.928,1.8,0.0), glm::vec3(0,180,0), "media/models/aldeana.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        trigger_sto.RegisterConversation(npc, trigger_sys, KeySound::Voces_NPC_oldWoman, 4);

        finalPos = glm::vec3(47.158, 2, -55.973);
    }

    /*                      LEVEL 4 POBLADO                        */

    else if(lvl == 4) {
        ManFacadeSound::GetInstance()->getFacade()->startEvent(KeySound::Musica_Level_3);
        //ManFacadeRender::GetInstance()->getFacade()->clearKeyHUD();

        ManFacadeRender::GetInstance()->getFacade()->setSkybox("media/skybox/right.bmp","media/skybox/left.bmp","media/skybox/top.bmp","media/skybox/bottom.bmp","media/skybox/front.bmp","media/skybox/back.bmp");
        ManFacadeRender::GetInstance()->getFacade()->deleteLights();
        ManFacadeRender::GetInstance()->getFacade()->addSceneDirectionalNodeLight(dir, amb, diff, spec, true);


        auto& key = GOFact.createObject(glm::vec3(-44.3607 ,3.6,-96.6177), glm::vec3(0,0,0), "media/models/llave.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(key);
        GOFact.createObject(glm::vec3(-69.7378 ,5.3, -60.8975), glm::vec3(0,270,0), "media/models/puerta.obj", glm::vec3(-3.0,-1.700,-1.350),glm::vec3(1.350,1.700,3.0));
        trigger_sto.RegisterKey(key,trigger_sys, 0);

        auto& beer = GOFact.createObject(glm::vec3(-3.0339,3.6,-46.928), glm::vec3(0,0,0), "media/models/hidromiel.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(beer);
        trigger_sto.RegisterBeer(beer,trigger_sys);

        auto& beer2 = GOFact.createObject(glm::vec3(-53.243,3.6,-26.96), glm::vec3(0,0,0), "media/models/hidromiel.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(beer2);
        trigger_sto.RegisterBeer(beer2,trigger_sys);

        auto& orb = GOFact.createObject(glm::vec3(-73.368,3.6, -62.1), glm::vec3(0,0,0), "media/models/orbePasoDeNivel.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(orb);
        sensoryMemory.registEnt2React(GOFact.createObject(glm::vec3(40.114,4.6,-37.879), glm::vec3(0,90,0), "media/models/auraPasoNivel.obj", glm::vec3(-0.5,-1.700,-0.5),glm::vec3(0.5,2,0.5)));
        trigger_sto.RegisterOrb(orb,trigger_sys);

        auto& palanca = GOFact.createObject(glm::vec3(13.424,3.512,-84.322), glm::vec3(0,90,0), "media/models/palanca.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(GOFact.createObject(glm::vec3(-21.408,3.8,-61.979), glm::vec3(0,90,0), "media/models/tablaPuenteAlta.obj",glm::vec3(-3.5, -1.5, -0.6),glm::vec3(3.5, 1.5, 0.5)));
        trigger_sto.RegisterLever(palanca,trigger_sys);

        auto& npc = GOFact.createObject(glm::vec3(66.768,4.3,-54.4), glm::vec3(0,180,0), "media/models/aldeano.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        trigger_sto.RegisterConversation(npc,trigger_sys, KeySound::Voces_NPC_villager, 5);

        finalPos = glm::vec3(40.363, 3.6, -37.5);
    }

    /*                      LEVEL 5 DESIERTO                        */

    else if(lvl == 5) {
        ManFacadeSound::GetInstance()->getFacade()->startEvent(KeySound::Musica_Level_2);
        //ManFacadeRender::GetInstance()->getFacade()->clearKeyHUD();
        ManFacadeRender::GetInstance()->getFacade()->setSkybox("media/skybox/right.bmp","media/skybox/left.bmp","media/skybox/top.bmp","media/skybox/bottom.bmp","media/skybox/front.bmp","media/skybox/back.bmp");
        
        ManFacadeRender::GetInstance()->getFacade()->deleteLights();
        ManFacadeRender::GetInstance()->getFacade()->addSceneDirectionalNodeLight(dir, amb, diff, spec, true);

        
        // KEYs
        auto& key = GOFact.createObject(glm::vec3(-15.319 ,1.3351,-71.874), glm::vec3(0,0,0), "media/models/llave2.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(key);
        sensoryMemory.registEnt2React(GOFact.createObject(glm::vec3(14.282 ,1.94,41.775), glm::vec3(0,0,0), "media/models/puertaCelda.obj", glm::vec3(-1.3,-1.700,-1.350),glm::vec3(1.350,1.700,3.0)));
        trigger_sto.RegisterKey(key,trigger_sys, 0);
        
        auto& key2 = GOFact.createObject(glm::vec3(-44.875 ,1.3351,73.811), glm::vec3(0,0,0), "media/models/llave.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(key2);
        sensoryMemory.registEnt2React(GOFact.createObject(glm::vec3(12.274 ,1.94,31.221), glm::vec3(0,0,0), "media/models/puertaCelda2.obj", glm::vec3(-1.3,-1.700,-1.350),glm::vec3(1.350,1.700,3.0)));
        trigger_sto.RegisterKey(key2,trigger_sys, 1);

        auto& key3 = GOFact.createObject(glm::vec3(2.9117 ,1.3351,-53.547), glm::vec3(0,0,0), "media/models/llave3.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(key3);
        sensoryMemory.registEnt2React(GOFact.createObject(glm::vec3(38.916,1.94,-15.521), glm::vec3(0,180,0), "media/models/puertaCelda3.obj", glm::vec3(-1.3,-1.700,-1.350),glm::vec3(1.350,1.700,3.0)));
        trigger_sto.RegisterKey(key3,trigger_sys, 2);

        auto& key4 = GOFact.createObject(glm::vec3(-15.499 ,1.3351,16.46), glm::vec3(0,0,0), "media/models/llave4.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(key4);
        sensoryMemory.registEnt2React(GOFact.createObject(glm::vec3(-22.072 ,1.94,-18.21), glm::vec3(0,180,0), "media/models/puertaCelda4.obj", glm::vec3(-1.3,-1.700,-1.350),glm::vec3(1.350,1.700,3.0)));
        trigger_sto.RegisterKey(key4,trigger_sys, 3);

        //BEERs
        auto& beer = GOFact.createObject(glm::vec3(-29.782,1.3351,30.37), glm::vec3(0,0,0), "media/models/hidromiel.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(beer);
        trigger_sto.RegisterBeer(beer,trigger_sys);

        auto& beer2 = GOFact.createObject(glm::vec3(14.943,1.3351,-2.3948), glm::vec3(0,0,0), "media/models/hidromiel.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(beer2);
        trigger_sto.RegisterBeer(beer2,trigger_sys);

        auto& beer3 = GOFact.createObject(glm::vec3(-35.918,1.3351,-28.534), glm::vec3(0,0,0), "media/models/hidromiel.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(beer3);
        trigger_sto.RegisterBeer(beer3,trigger_sys);

        //ORB
        auto& orb = GOFact.createObject(glm::vec3(0.57577,1.3351, 42.854), glm::vec3(0,0,0), "media/models/orbePasoDeNivel.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(orb);
        sensoryMemory.registEnt2React(GOFact.createObject(glm::vec3(23.612,2.2618,-27.265), glm::vec3(0,90,0), "media/models/auraPasoNivel.obj", glm::vec3(-0.5,-1.700,-0.5),glm::vec3(0.5,2,0.5)));
        trigger_sto.RegisterOrb(orb,trigger_sys);

        //PALANCA
        auto& palanca = GOFact.createObject(glm::vec3(-20.849,0.7,-43.54), glm::vec3(0,90,0), "media/models/palanca.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        sensoryMemory.registEnt2React(GOFact.createObject(glm::vec3(4.6262,3.2528,-38.779), glm::vec3(0,180,0), "media/models/tablaPuenteAlta.obj",glm::vec3(-3.5, -1.5, -0.6),glm::vec3(3.5, 1.5, 0.5)));
        trigger_sto.RegisterLever(palanca,trigger_sys);

        //NPC
        auto& npc = GOFact.createObject(glm::vec3(-2.766,1.6,39.56), glm::vec3(0,0,0), "media/models/pariaMasculino.obj",glm::vec3(-0.5,-1.5,-0.25),glm::vec3(0.5,1.5,0.25));
        trigger_sto.RegisterConversation(npc,trigger_sys, KeySound::Voces_NPC_prisonerSafe, 6);

        finalPos = glm::vec3(23.556, 2, -28.036);
    }

    // Return cursor to center
    //auto scrSize { ManFacadeRender::GetInstance()->getFacade()->getScreenSize() };
    //ManFacadeInput::GetInstance()->getFacade()->setMousePosition( scrSize.x/2, scrSize.y/2 );
    //ManFacadeRender::GetInstance()->getFacade()->update();
}



Level::~Level() {
    Entity::restartCountID();
    ID::restartCountID();
}



void
Level::update(float deltaTime) {
    bool triggerActivate { false };

    camera_sys.update( entity_man );
    position_sys.update( entity_man );
    triggerActivate = trigger_sys.update(entity_man,collision_sys,deltaTime);
    render_sys.update( entity_man, deltaTime, triggerActivate);


    if( !triggerActivate ) {
        input_sys.update( entity_man, deltaTime);
        ai_sys.update( entity_man, deltaTime );
        depuration_sys.update( entity_man, deltaTime );
        physics_sys.update( entity_man, deltaTime);
        collision_sys.update( entity_man);
        sensorial_sys.update(entity_man, deltaTime);
        lod_sys.update(entity_man, deltaTime);
        behaviour_sys.update(entity_man, collision_sys);
        arrow_sys.update(entity_man, deltaTime);
        schedul_sys.update( entity_man );
        weapon_sys.update(entity_man, deltaTime);
        if(player.heal->health > 0){
            health_sys.update( entity_man );
        }
    }

    if( Blackboard::GetInstance()->getTimesDiscovered() >= Blackboard::GetInstance()->maxTimesDiscovered){
        player.heal->health = 0;
        ManFacadeRender::GetInstance()->getFacade()->drawStealthBar(5);
    }

    if(input_sys.isKeyPressed(KeyCode::KEY_ESCAPE) || !render_sys.isDeviceRunning() 
    || player.heal->health <= 0  ||
    input_sys.isKeyPressed(KeyCode::KEY_KEY_N) || glm::distance(player.pos->position, finalPos) < 2) {

        if(player.heal->health <= 0){
            SM.pushState<PauseMenu>(true);
            ManFacadeRender::GetInstance()->getFacade()->drawHud(player);
        }

        playing = false;

        // Stop current music and level
        if ( lvl == 0 ) {
            ManFacadeSound::GetInstance()->getFacade()->stopEvent(KeySound::Ambientes_forest_2);
            //ManFacadeSound::GetInstance()->getFacade()->stopEvent(KeySound::Voces_NPC_stealthTrainer);
            //ManFacadeSound::GetInstance()->getFacade()->stopEvent(KeySound::Voces_NPC_speedTrainer);
            //ManFacadeSound::GetInstance()->getFacade()->stopEvent(KeySound::Voces_NPC_attackTrainer);
        } else if ( lvl == 1 ) {
            ManFacadeSound::GetInstance()->getFacade()->stopEvent(KeySound::Ambientes_forest_2);
        } else if ( lvl == 2 ) {
            ManFacadeSound::GetInstance()->getFacade()->stopEvent(KeySound::Musica_Level);
            //ManFacadeSound::GetInstance()->getFacade()->stopEvent(KeySound::Voces_NPC_prisoner);
        } else if ( lvl == 3 ) {
            ManFacadeSound::GetInstance()->getFacade()->stopEvent(KeySound::Ambientes_forest_2);
            //ManFacadeSound::GetInstance()->getFacade()->stopEvent(KeySound::Voces_NPC_oldWoman);
        } else if ( lvl == 4 ) {
            ManFacadeSound::GetInstance()->getFacade()->stopEvent(KeySound::Musica_Level_3);
            //ManFacadeSound::GetInstance()->getFacade()->stopEvent(KeySound::Voces_NPC_villager);
        } else if ( lvl == 5 ) {
            ManFacadeSound::GetInstance()->getFacade()->stopEvent(KeySound::Musica_Level_2);
            //ManFacadeSound::GetInstance()->getFacade()->stopEvent(KeySound::Voces_NPC_prisonerSafe);
        }

        if(input_sys.isKeyPressed(KeyCode::KEY_KEY_N) || glm::distance(player.pos->position,finalPos) < 2){ // FIXED == si el player llega al rango de paso de nivel
            Blackboard::GetInstance()->restartDiscoveredTimes();
            //ManFacadeRender::GetInstance()->getFacade()->clearConver();
            lvl++;
            render_sys.cleanScene();
            ManFacadeRender::GetInstance()->getFacade()->pauseInit(true);
            if (lvl != 6)
                ManFacadeRender::GetInstance()->getFacade()->paintChargeScreen();
            ManFacadeRender::GetInstance()->getFacade()->update();
        }
        
    }

    ManFacadeSound::GetInstance()->getFacade()->update();
    

    if(input_sys.isKeyPressed(KeyCode::KEY_KEY_P) && timeReturnPause <= 0){
        SM.pushState<PauseMenu>(false);
        timeReturnPause = 0.5;
    }else
        timeReturnPause -= deltaTime;
}



bool
Level::alive() {
    return playing;
}





GameManager::GameManager(ARCS::StateManager& sm, ARCS::RenderSystem& rs)
    :   SM{sm}
    ,   render_sys{rs}
{ }



GameManager::~GameManager(){
    //ManFacadeRender::GetInstance()->getFacade()->menuInit();
    ManFacadeSound::GetInstance()->getFacade()->startEvent(KeySound::Musica_Soundtrack_Inicio);
}
    


void
GameManager::update(float deltaTime) {
    if( ManFacadeInput::GetInstance()->getFacade()->isKeyPressed(static_cast<int>(KeyCode::KEY_ESCAPE)) ||  !render_sys.isDeviceRunning() ) {
        playing = false;
        return;
    }
    bool lv = false;
    if(lastlevel==level){
        lv = true;
    }
    
    lastlevel=level;

    if(level == 0){
        SM.pushState<Level>(SM,level,"media/levels/tutorial.json",render_sys, lv);
    }else if(level == 1){
        SM.pushState<Level>(SM,level, "media/levels/nivelIntermedio.json",render_sys, lv);
    }else if(level == 2){
        SM.pushState<Level>(SM,level, "media/levels/nivel1.json",render_sys, lv);
    }else if(level == 3){
        SM.pushState<Level>(SM,level, "media/levels/nivel2.json",render_sys, lv);
    }else if(level == 4){
        SM.pushState<Level>(SM,level, "media/levels/nivel3.json",render_sys, lv);
    }else if(level == 5){
        SM.pushState<Level>(SM,level, "media/levels/nivel4.json",render_sys, lv);
    }else{
        playing = false;
    }
}



bool
GameManager::alive() {
    return playing;
}



void
GameManager::nextLevel() {
    ++level;
}




} // namespace ARCS