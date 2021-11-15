#include <manager/GameContext.hpp>
#include <facade/Render/ManFacadeRender.hpp>
#include <facade/Physics/ManFacadePhysics.hpp>
#include <facade/Sound/ManFacadeSound.hpp>
#include "HealthSystem.hpp"
#include "CollisionSystem.hpp"


namespace ARCS {

HealthSystem::HealthSystem(const ARCS::CollisionSystem &cs)
    : colsys { cs }
{ }


bool HealthSystem::update(GameContext &gc) const {
    auto& healCmpVec { gc.getHealthComponents() };
    Entity* player = 0;
    //int contInvisibility = 0;
    bool timeKill = false;

    for (auto& heal : healCmpVec) {
        auto* ent = gc.getEntityById(heal.getEntityID());
        if (!ent) continue;

        if (heal.health) {

            if (ent->inp) {
                player = gc.getEntityById(heal.getEntityID());
            } else {
                calculateOrientation(player, ent);        // TODO FACADE: Descomentar cuando la vida de los enemigos este añadida
                if (glm::distance(player->pos->position, ent->pos->position) <= player->wc->limitDistance4Attacking && ent->sens && ent->sens->clueless){
                    timeKill = true;
                }

                if (player->wc && ent->col && player->wc->time2HitAgain >= player->wc->limitTime4Waiting && player->wc->hiting && colsys.checkObjectCollision(ent->col->boxRoot, player->wc->boxWeapon,ent->pos->position,player->pos->position + player->wc->wpositionRelative)){
                    if(ent->sens && ent->sens->clueless) {
                        heal.health = 0;
                        
                        if(ent->wc)
                            ent->wc->hiting = false;
                    } else {
                        --heal.health;
                        if ( ent->ai )
                            ManFacadeRender::GetInstance()->getFacade()->doActionAnimation(heal.getEntityID(),3);
                        calculateLife(heal);
                    }

                    player->wc->displacement = player->wc->limitDistance4Attacking;        // FIXED: Puntero desreferenciado
                    ManFacadeSound::GetInstance()->getFacade()->set3DAttributes(KeySound::Voces_Masculinas_hurt_enemy_men, ent->pos->position, player->pos->position, player->pos->rotation);
                    ManFacadeSound::GetInstance()->getFacade()->startEvent(KeySound::Voces_Masculinas_hurt_enemy_men);
                }
            }

            if(ent->id != player->id) {
                if(ent->wc && ent->wc->time2HitAgain >= ent->wc->limitTime4Waiting && ent->wc->hiting && colsys.checkObjectCollision(player->col->boxRoot, ent->wc->boxWeapon,player->pos->position,ent->pos->position + ent->wc->wpositionRelative)){
                    --player->heal->health;
                    ManFacadeRender::GetInstance()->getFacade()->drawHud(*player);
                    ent->wc->displacement = ent->wc->limitDistance4Attacking;  
                    startDamageSound(player);
                }
            }

        } else if (ent->phy) {
            gc.destroyEntityById( heal.getEntityID() );
            ManFacadeRender::GetInstance()->getFacade()->setVisible(heal.getEntityID(), false);

        }

        // Check arrow impact
        if ( ent->arr ) {
            auto* arrowEnt { gc.getEntityById(ent->arr->arrowID) };
            if ( !arrowEnt  ||  !arrowEnt->wc->hiting ) continue;

            if (colsys.checkObjectCollision(player->col->boxRoot, arrowEnt->wc->boxWeapon, player->pos->position, arrowEnt->pos->position)) {
                --player->heal->health;
                ManFacadeRender::GetInstance()->getFacade()->drawHud(*player);
                arrowEnt->wc->hiting = false;
                ManFacadeRender::GetInstance()->getFacade()->setNoVisible(arrowEnt->id);
                startDamageSound(player);
            }
        }

    }

    if (timeKill) {
        ManFacadeRender::GetInstance()->getFacade()->drawKill();
    }else{
        ManFacadeRender::GetInstance()->getFacade()->clearKill();
    }

    return true;
}


bool
HealthSystem::leafNodeCollided(const BoundingBoxNode& bn) const {
    if ( bn.childs.empty() ) {
        return bn.collided;
    } else if (bn.collided) {
        for (const auto& b : bn.childs)
            if ( leafNodeCollided(b) )
                return true;
    }
    return false;
}


void
HealthSystem::startDamageSound(Entity* player) const {
    ManFacadeSound::GetInstance()->getFacade()->startEvent(KeySound::Voces_hurt_main);
}



float
HealthSystem::adjustRadians(float rad) const {
    float radians { rad };

    while (radians >= 2*PI)
        radians -= 2*PI;
    while (radians < 0)
        radians += 2*PI;

    return radians;
}



void
HealthSystem::calculateOrientation(Entity* player, Entity *enemy) const {
    if(player && enemy){
        ManFacadePhysics::GetInstance()->getFacade()->setMeshRotation(enemy->id + 6000, glm::vec3(0, player->pos->rotation.y, 0));
        ManFacadePhysics::GetInstance()->getFacade()->setMeshPosition(enemy->id + 6000, enemy->pos->position);
    }
}



void HealthSystem::calculateLife(HealthComponent &heal) const{
    float aux { (heal.health/(float)heal.maxHP) * 100 };
    int id { heal.getEntityID() + 6000 };


    if (aux <= 80 && aux > 60) {
        ManFacadeRender::GetInstance()->getFacade()->setTextureNode(id, "vidaEnemigo4"); //4
    } else if (aux <= 60 && aux > 40) {
        ManFacadeRender::GetInstance()->getFacade()->setTextureNode(id, "vidaEnemigo3"); //3
    } else if (aux <= 40 && aux > 20) {
        ManFacadeRender::GetInstance()->getFacade()->setTextureNode(id, "vidaEnemigo2"); //2
    } else if (aux <= 20 && aux > 0) {
        ManFacadeRender::GetInstance()->getFacade()->setTextureNode(id, "vidaEnemigo1"); //1
    } else if (aux == 0) {
        ManFacadeRender::GetInstance()->getFacade()->setTextureNode(id, "vidaEnemigo0"); //0
        ManFacadeRender::GetInstance()->getFacade()->setNoVisible(id);
    }
}

} // namespace ARCS