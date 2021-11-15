#include <manager/GameContext.hpp>
#include <facade/Render/ManFacadeRender.hpp>
#include <TriggerSystem/TriggerSystem.hpp>
#include <facade/Sound/ManFacadeSound.hpp>
#include <util/KeyCodes.hpp>
#include "InputSystem.hpp"

namespace ARCS {

InputSystem::InputSystem() :
    manInputFacade  {  ManFacadeInput::GetInstance() },
    manRenderFacade { ManFacadeRender::GetInstance() }
{
    auto scrCenter { manRenderFacade->getFacade()->getScreenCenterPosition() };
    manInputFacade->getFacade()->setMousePosition(scrCenter.x, scrCenter.y);
    ManFacadeRender::GetInstance()->getFacade()->initStam();
}

InputSystem::~InputSystem() {
    //delete manInputFacade;
    manInputFacade  = 0;
    manRenderFacade = 0;
}

bool
InputSystem::update(GameContext& gc, float dt) {
    auto& inpVecCmp { gc.getInputComponents() };;

    for (auto& inp : inpVecCmp) {
        auto* phy { gc.getPhysicsComponentByID( inp.getEntityID() ) };
        auto* sens { gc.getSensorialPerceptionComponentByID( inp.getEntityID() ) };
        auto* col { gc.getCollisionComponentByID( inp.getEntityID() ) };
        auto* cam { gc.getEntityById(gc.getCameraComponents()[0].getEntityID())};
        auto* wc  { gc.getEntityById( inp.getEntityID() )->wc   };

        if (!phy  &&  !wc) continue;
        phy->speedLinearVector.x = phy->speedLinearVector.z = 0;
        phy->speedAngularVector.y = 0;

        // Entity Running
        if (isKeyPressed(KeyCode::KEY_KEY_W) )
            phy->speedLinearVector.x = 1;
        else if ( isKeyPressed(KeyCode::KEY_KEY_S) )
            phy->speedLinearVector.x = -1;

        if (isKeyPressed(KeyCode::KEY_KEY_A) )
            phy->speedLinearVector.z = -1;
        else if (isKeyPressed(KeyCode::KEY_KEY_D) )
            phy->speedLinearVector.z = 1;

        // STAMINA SE GASTA
        if ( isKeyPressed(KeyCode::KEY_LSHIFT)  &&  inp.stamina > 0  &&  phy->isMovingAhead() ){
            //ManFacadeRender::GetInstance()->getFacade()->drawStam(*gc.getEntityById(inp.getEntityID()));
            phy->speedLinear = phy->sprintSpeed;
            inp.stamina -= dt;

            if(sens)
                sens->rSense.noise.box = {{-8,-8,-8},{8,8,8}}; 
            if(col)
                col->boxRoot.box = {{-1,-1,-1},{1,1,1}};
            
            if(cam->cam->crouched){      
                cam->pos->position.y += cam->cam->distanceCrouchedDown;
                cam->cam->crouched = false;
                cam->cam->direction.y -= cam->cam->distanceCrouchedDown;         
            }   
        }
        else if (isKeyPressed(KeyCode::KEY_LCONTROL) )  {
            if(!cam->cam->crouched){
                phy->speedLinear = phy->normalSpeed - 2.5f;   
                cam->pos->position.y -= cam->cam->distanceCrouchedDown;
                cam->cam->crouched = true;
                cam->cam->direction.y += cam->cam->distanceCrouchedDown; //FIXED = cambiar solo una vez
                if(sens)
                    sens->rSense.noise.box = {{0,0,0},{0,0,0}};  
                if(col)
                    col->boxRoot.box = {{-0.8,-1,-0.8},{0.8,-0.5,0.8}};
            }
        }    
        else{
            phy->speedLinear = phy->normalSpeed;
            if(sens)
                sens->rSense.noise.box = {{-5,-5,-5},{5,5,5}}; 
            if(col)
                col->boxRoot.box = {{-0.8,-1,-0.8},{0.8,1,0.8}};
            
            if(cam->cam->crouched){           
                cam->pos->position.y += cam->cam->distanceCrouchedDown;
                cam->cam->crouched = false;
                cam->cam->direction.y -= cam->cam->distanceCrouchedDown;
            }
        }

        // STAMINA SE LLENA
        ManFacadeRender::GetInstance()->getFacade()->drawStam(*gc.getEntityById(inp.getEntityID()));

        if(inp.stamina <= 0){
            if(inp.recover <= inp.kTimeRecoverStamina) {  
                inp.recover += dt;
            }else {
                inp.stamina = inp.kLimitDurationRun;
                inp.recover -= inp.kTimeRecoverStamina;
            }
        } else if(!isKeyPressed(KeyCode::KEY_LSHIFT)) {
            inp.stamina += dt/2;
            if(inp.stamina > 1.8) inp.stamina = inp.kLimitDurationRun;;
        }

        // Acceleration
        if(phy->speedLinearVector.x == 0  &&  phy->speedLinearVector.z == 0) {
            sens->rSense.noise.box = {{0,0,0},{0,0,0}}; // if dont move do not do noise
            phy->speedLinearVector.y = 0;
        } else {
            phy->speedLinearVector.y = 1;
        }

        // Entity Rotation
        auto& camcmp { gc.getCameraComponents()[0] };
        auto mousePos  { manInputFacade->getFacade()->getMousePosition()         };
        auto scrCenter { manRenderFacade->getFacade()->getScreenCenterPosition() };
        phy->speedAngularVector.y = (mousePos.x - scrCenter.x) * inp.kPercentageMouseSpeed.x;
        camcmp.direction.y += (scrCenter.y - mousePos.y) * dt * inp.kPercentageMouseSpeed.y;
        //manInputFacade->getFacade()->setMousePosition(scrCenter.x, scrCenter.y);
        
        // Entity Attack
        if(!wc->hiting) {
            if(isKeyPressed(KeyCode::KEY_SPACE) || isMouseLeftDown()) {
                if(wc->time2HitAgain >= wc->limitTime4Waiting) {
                    manRenderFacade->getFacade()->doActionAnimation(inp.getEntityID(),0);
                    ManFacadeSound::GetInstance()->getFacade()->startEvent(KeySound::Efectos_atack_main);
                    wc->displacement = 0;
                    wc->hiting = true;
                }
            }
        }
    }
    
    return true;
}


bool
InputSystem::isKeyPressed(KeyCode key) {
    return manInputFacade->getFacade()->isKeyPressed( static_cast<int>(key) );
}

bool
InputSystem::isMouseLeftDown() const {

    return manInputFacade->getFacade()->isMouseLeftDown();
}



} // namespace ARCS
