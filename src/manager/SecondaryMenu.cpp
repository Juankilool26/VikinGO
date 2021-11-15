#include "SecondaryMenu.hpp"
#include <facade/Render/ManFacadeRender.hpp>
#include <facade/Input/ManFacadeInput.hpp>
#include <facade/Sound/ManFacadeSound.hpp>
#include <util/KeyCodes.hpp>

SecondaryMenu::SecondaryMenu(ARCS::StateManager& sm, ARCS::RenderSystem& rs,int n) : SM{sm}, render_sys{rs}{
    option = n;
}

SecondaryMenu::~SecondaryMenu(){
  ManFacadeRender::GetInstance()->getFacade()->cleanScene();
  ManFacadeRender::GetInstance()->getFacade()->menuInit();
  ManFacadeRender::GetInstance()->getFacade()->menuOptions(option + 1);
}

void SecondaryMenu::update(float delta){
    if(((ManFacadeInput::GetInstance()->getFacade()->isKeyPressed(static_cast<int>(KeyCode::KEY_ESCAPE)) && timeToChangeOption <= 0)) || 
    !ManFacadeRender::GetInstance()->getFacade()->isDeviceRunning()){
        m_alive = false;
    }
    else{
        if(option == 0){
            if(timeToChangeOption <= 0 && (ManFacadeInput::GetInstance()->getFacade()->isKeyPressed(static_cast<int>(KeyCode::KEY_SPACE)) ||
                ManFacadeInput::GetInstance()->getFacade()->isKeyPressed(static_cast<int>(KeyCode::KEY_RETURN)))){
                ManFacadeRender::GetInstance()->getFacade()->menuOptions(gender);
                ManFacadeSound::GetInstance()->getFacade()->startEvent(KeySound::Menus_Enter);
                ManFacadeSound::GetInstance()->getFacade()->stopEvent(KeySound::Musica_Soundtrack_Inicio);
                SM.pushState<ARCS::GameManager>(SM,render_sys);
                ManFacadeRender::GetInstance()->getFacade()->cleanScene();
                m_alive = false;
            }

            if(timeToChangeOption <= 0){
                if(ManFacadeInput::GetInstance()->getFacade()->isKeyPressed(static_cast<int>(KeyCode::KEY_LEFT)) && gender != 4){
                    --gender;
                    timeToChangeOption = 0.15;
                    ManFacadeRender::GetInstance()->getFacade()->secondaryInit(gender);
                    ManFacadeSound::GetInstance()->getFacade()->startEvent(KeySound::Menus_Options);
                }

                else if(ManFacadeInput::GetInstance()->getFacade()->isKeyPressed(static_cast<int>(KeyCode::KEY_RIGHT)) && gender != 6){
                    ++gender;
                    timeToChangeOption = 0.15;
                    ManFacadeRender::GetInstance()->getFacade()->secondaryInit(gender);
                    ManFacadeSound::GetInstance()->getFacade()->startEvent(KeySound::Menus_Options);
                }
            } else {
                timeToChangeOption -=delta;
            }
        }else{
            timeToChangeOption -=delta;
        }

        if(!m_alive){
            ManFacadeRender::GetInstance()->getFacade()->paintChargeScreen();
        }
    }


    ManFacadeRender::GetInstance()->getFacade()->update();

    
}