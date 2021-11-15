#include "PauseMenu.hpp"
#include <facade/Render/ManFacadeRender.hpp>
#include <facade/Input/ManFacadeInput.hpp>
#include <facade/Sound/ManFacadeSound.hpp>
#include <Blackboard/Blackboard.hpp>
#include <util/KeyCodes.hpp>

PauseMenu::PauseMenu(bool die){
    gameOver = die;
    ManFacadeRender::GetInstance()->getFacade()->pauseInit(die);
    
    if(!die) {
        ManFacadeSound::GetInstance()->getFacade()->startEvent(KeySound::Menus_Pause);
    }else{
        timeToQuitPause = 3.0;
    }
}

PauseMenu::~PauseMenu(){
    ManFacadeRender::GetInstance()->getFacade()->pauseClean();
}

void PauseMenu::update(float delta){
    ManFacadeRender::GetInstance()->getFacade()->update();
    if(!gameOver){
        if(((ManFacadeInput::GetInstance()->getFacade()->isKeyPressed(static_cast<int>(KeyCode::KEY_KEY_P)) && timeToQuitPause <= 0)) || 
        ManFacadeInput::GetInstance()->getFacade()->isKeyPressed(static_cast<int>(KeyCode::KEY_ESCAPE)) || !ManFacadeRender::GetInstance()->getFacade()->isDeviceRunning()){
            m_alive = false;
        }
        ManFacadeSound::GetInstance()->getFacade()->update();
    }
    else{
        if(timeToQuitPause <= 0 || 
        ManFacadeInput::GetInstance()->getFacade()->isKeyPressed(static_cast<int>(KeyCode::KEY_ESCAPE)) || !ManFacadeRender::GetInstance()->getFacade()->isDeviceRunning()){
            m_alive = false;
            Blackboard::GetInstance()->restartDiscoveredTimes();
            ManFacadeRender::GetInstance()->getFacade()->cleanScene();
        }
    }
    
    timeToQuitPause -=delta;
}