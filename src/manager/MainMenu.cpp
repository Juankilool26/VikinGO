#include "MainMenu.hpp"
#include "SecondaryMenu.hpp"
#include <facade/Sound/ManFacadeSound.hpp>

MainMenu::MainMenu(ARCS::StateManager& sm, ARCS::RenderSystem& rs) : SM{sm}, render_sys{rs} {
    ManFacadeRender::GetInstance()->getFacade()->menuInit();
    ManFacadeSound::GetInstance()->getFacade()->startEvent(KeySound::Musica_Soundtrack_Inicio);
}

MainMenu::~MainMenu(){
    ManFacadeSound::GetInstance()->getFacade()->stopEvent(KeySound::Musica_Soundtrack_Inicio);
    render_sys.dropDevice();
}

void MainMenu::update(float delta) {
    
    if(ManFacadeInput::GetInstance()->getFacade()->isKeyPressed(static_cast<int>(KeyCode::KEY_SPACE)) ||
       ManFacadeInput::GetInstance()->getFacade()->isKeyPressed(static_cast<int>(KeyCode::KEY_RETURN))){
        ManFacadeRender::GetInstance()->getFacade()->menuOptions(option);
        ManFacadeSound::GetInstance()->getFacade()->startEvent(KeySound::Menus_Enter);

        if(option == 1){
            SM.pushState<SecondaryMenu>(SM,render_sys,0);
            ManFacadeRender::GetInstance()->getFacade()->secondaryInit(0);
        } 
        
        if(option == 2){
            SM.pushState<SecondaryMenu>(SM,render_sys,1);
            ManFacadeRender::GetInstance()->getFacade()->secondaryInit(1);
        }

        if(option == 3){
            SM.pushState<SecondaryMenu>(SM,render_sys,2);
            ManFacadeRender::GetInstance()->getFacade()->secondaryInit(2);
        }

        if(option == 4){
            render_sys.dropDevice();
        }
    }
    ManFacadeSound::GetInstance()->getFacade()->update();
    if(!render_sys.isDeviceRunning()){
        m_alive = false;
    }	

    if(timeToChangeOption >= 0.15){
        if(ManFacadeInput::GetInstance()->getFacade()->isKeyPressed(static_cast<int>(KeyCode::KEY_UP)) && option != 1){
            --option;
            timeToChangeOption = 0;
            ManFacadeRender::GetInstance()->getFacade()->menuOptions(option);
            ManFacadeSound::GetInstance()->getFacade()->startEvent(KeySound::Menus_Options);
        }

        else if(ManFacadeInput::GetInstance()->getFacade()->isKeyPressed(static_cast<int>(KeyCode::KEY_DOWN)) && option != 4){
            ++option;
            timeToChangeOption = 0;
            ManFacadeRender::GetInstance()->getFacade()->menuOptions(option);
            ManFacadeSound::GetInstance()->getFacade()->startEvent(KeySound::Menus_Options);
        }
    } else {
        timeToChangeOption += delta;
    }

    ManFacadeRender::GetInstance()->getFacade()->update();
}