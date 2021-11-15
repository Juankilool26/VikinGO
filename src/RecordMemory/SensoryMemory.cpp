#include "SensoryMemory.hpp"
#include <Blackboard/Blackboard.hpp>
#include <facade/Sound/ManFacadeSound.hpp>
#include <cmath>


SensoryMemory::SensoryMemory(ARCS::Entity& c_player, float c_memorySpan) : player{c_player} {
    memorySpan = c_memorySpan;
    ent2React.reserve(20); 
}


SensoryMemory::~SensoryMemory() {
    m_memoryMap.clear();
    ent2React.clear();
}


void SensoryMemory::makeNewRecordIfNotAlreadyPresent(ARCS::Entity* entityPtr) {    //comprueba si hay un recuerdo sino crea uno y lo anyade al memoryMap
    if(m_memoryMap.find(entityPtr) == m_memoryMap.end()) {          //not found
        MemoryRecord m_memoryRecord;
        m_memoryMap.insert(std::pair<ARCS::Entity*, MemoryRecord>(entityPtr, m_memoryRecord));
    } 
}


bool
SensoryMemory::isPlayerNear(ARCS::Entity& enemy) {
    bool isNear { false };
    auto distanceX { glm::abs(player.pos->position.x - enemy.pos->position.x) };
    auto distanceZ { glm::abs(player.pos->position.z - enemy.pos->position.z) };

    isNear = ( glm::sqrt( glm::pow(distanceX, 2) + glm::pow(distanceZ, 2) )  <=  enemy.sens->kMinDistance2Face );
    return isNear;
}


void SensoryMemory::updateSound(ARCS::Entity *enemy) {  
    makeNewRecordIfNotAlreadyPresent(enemy);
    if(m_memoryMap.find(enemy) != m_memoryMap.end()) {
        std::map<ARCS::Entity*, MemoryRecord>::iterator curMap;
        curMap = m_memoryMap.find(enemy);
        curMap->second.timeLastSensed = 0;
        curMap->second.lastSensePosition = player.pos->position;

        if(!curMap->second.sensed && enemy->isAlive()){
            ManFacadeRender::GetInstance()->getFacade()->setVisible(enemy->id + 5000, true);
            Blackboard::GetInstance()->oneDiscovers();
            curMap->second.sensed = true;
            ManFacadeSound::GetInstance()->getFacade()->set3DAttributes(KeySound::Voces_Masculinas_iHeardSomething, enemy->pos->position, player.pos->position, player.pos->rotation);
            ManFacadeSound::GetInstance()->getFacade()->startEvent(KeySound::Voces_Masculinas_iHeardSomething);
        }

        if(curMap->second.hittable && !isPlayerNear(*enemy)){
            ManFacadeRender::GetInstance()->getFacade()->doActionAnimation(enemy->id, 2);
        }

        curMap->second.hittable = isPlayerNear(*enemy);
        enemy->ai->inPatrol = false;
        enemy->sens->clueless = false;
        enemy->phy->speedLinear = enemy->phy->sprintSpeed -2;
    }
}


void SensoryMemory::updateVision(ARCS::Entity *enemy) {
    makeNewRecordIfNotAlreadyPresent(enemy);
    if(m_memoryMap.find(enemy) != m_memoryMap.end()) {
        std::map<ARCS::Entity*, MemoryRecord>::iterator curMap;
        curMap = m_memoryMap.find(enemy);
        curMap->second.timeLastSensed = 0;
        curMap->second.timeLastVisible = 0;
        curMap->second.lastSensePosition = player.pos->position;

        if ( enemy->isAlive() ) {
            if (!curMap->second.sensed) {
                ManFacadeRender::GetInstance()->getFacade()->setVisible(enemy->id + 5000, true);
                curMap->second.sensed = true;
                enemy->ai->inPatrol = false;
                ManFacadeSound::GetInstance()->getFacade()->set3DAttributes(KeySound::Voces_Masculinas_iHeardSomething, enemy->pos->position, player.pos->position, player.pos->rotation);
                ManFacadeSound::GetInstance()->getFacade()->startEvent(KeySound::Voces_Masculinas_iHeardSomething);
            }

            if(curMap->second.withinFOV) {
                    
                curMap->second.timeBecameVisible = 0;
                curMap->second.withinFOV = false;
                enemy->phy->speedLinear = enemy->phy->sprintSpeed;
                enemy->sens->clueless = false;
                ManFacadeRender::GetInstance()->getFacade()->doActionAnimation(enemy->id,2);
                ManFacadeSound::GetInstance()->getFacade()->set3DAttributes(KeySound::Voces_Masculinas_iSeeU, enemy->pos->position, player.pos->position, player.pos->rotation);
                ManFacadeSound::GetInstance()->getFacade()->startEvent(KeySound::Voces_Masculinas_iSeeU);
            }
        }
        if(curMap->second.hittable && !isPlayerNear(*enemy)){
            ManFacadeRender::GetInstance()->getFacade()->doActionAnimation(enemy->id, 2);
        }
        curMap->second.hittable = isPlayerNear(*enemy);
        
    }  
    
}


void SensoryMemory::checkToForget(ARCS::Entity* enemy, float delta){
    if(m_memoryMap.find(enemy) != m_memoryMap.end()) {
        std::map<ARCS::Entity*, MemoryRecord>::iterator curMap;
        curMap = m_memoryMap.find(enemy);

        if(curMap->second.timeLastVisible > memorySpan){
            curMap->second.withinFOV = true;  
        } else {
            curMap->second.timeLastVisible += delta;
            curMap->second.lastSensePosition = player.pos->position;
        }

        if(curMap->second.timeLastSensed > memorySpan){
            ManFacadeRender::GetInstance()->getFacade()->setVisible(enemy->id + 5000, false);
            curMap->second.sensed = false;
            enemy->phy->speedLinear = 2;
            enemy->sens->clueless = true;
            ManFacadeRender::GetInstance()->getFacade()->doActionAnimation(enemy->id,0);
        } else {
            curMap->second.timeLastSensed += delta;      
        }
        
        if(curMap->second.hittable && !isPlayerNear(*enemy)){
            ManFacadeRender::GetInstance()->getFacade()->doActionAnimation(enemy->id, 2);
        }
        if ( !isPlayerNear(*enemy) )
            curMap->second.hittable = false; 
    }
}


glm::vec3 SensoryMemory::getLastRecordedPositionOfOpponent(ARCS::Entity* enemy) const {
    std::map<ARCS::Entity*, MemoryRecord>::const_iterator curMap;
    glm::vec3 dev(0,0,0);

    if(m_memoryMap.find(enemy) != m_memoryMap.end()) {
        curMap = m_memoryMap.find(enemy);
        dev = curMap->second.lastSensePosition;
    }

    return dev;
}


void SensoryMemory::setLastRecordedPositionOfOpponent(ARCS::Entity* enemy, glm::vec3& pos, float& t){
    std::map<ARCS::Entity*, MemoryRecord>::iterator curMap;


    if(m_memoryMap.find(enemy) != m_memoryMap.end()) {
        curMap = m_memoryMap.find(enemy);
        curMap->second.lastSensePosition = pos;
        curMap->second.sensed = true;
        enemy->ai->inPatrol = false;
        curMap->second.timeLastSensed = t;
    }
}


float SensoryMemory::getTimeOpponentHasBeenVisible(ARCS::Entity* enemy) const {
    std::map<ARCS::Entity*, MemoryRecord>::const_iterator curMap;
        float dev = 0;

    if(m_memoryMap.find(enemy) != m_memoryMap.end()) {
        curMap = m_memoryMap.find(enemy);
        dev = curMap->second.timeBecameVisible;
    }

    return dev;
}


float SensoryMemory::getTimeSinceLastSensed(ARCS::Entity* enemy) const {
    std::map<ARCS::Entity*, MemoryRecord>::const_iterator curMap;
    float dev = 0;

    if(m_memoryMap.find(enemy) != m_memoryMap.end()) {
        curMap = m_memoryMap.find(enemy);
        dev = curMap->second.timeLastSensed;
    }

    return dev;
}


float SensoryMemory::getTimeOpponentHasBeenOutOfView(ARCS::Entity* enemy) const {
    std::map<ARCS::Entity*, MemoryRecord>::const_iterator curMap;
    float dev = 0;

    if(m_memoryMap.find(enemy) != m_memoryMap.end()) {
        curMap = m_memoryMap.find(enemy);
        dev = curMap->second.timeLastVisible;
    }

    return dev;
}


MemoryRecord& SensoryMemory::getMemoryRecordFromMap(ARCS::Entity* e)
{
    makeNewRecordIfNotAlreadyPresent(e);
    return m_memoryMap.find(e)->second;
}


bool SensoryMemory::isOponentHittable(ARCS::Entity* enemy) {  
    std::map<ARCS::Entity*, MemoryRecord>::iterator curMap;
    bool dev = false;

    if(m_memoryMap.find(enemy) != m_memoryMap.end()) {
        curMap = m_memoryMap.find(enemy);
        dev = curMap->second.hittable;
    }

    return dev;
}


bool SensoryMemory::isWithinFOV(ARCS::Entity* enemy){
    std::map<ARCS::Entity*, MemoryRecord>::iterator curMap;
    bool dev = false;

    if(m_memoryMap.find(enemy) != m_memoryMap.end()) {
        curMap = m_memoryMap.find(enemy);
        dev = curMap->second.withinFOV;
    }

    return dev;
}


bool SensoryMemory::isSensed(ARCS::Entity* enemy){
    std::map<ARCS::Entity*, MemoryRecord>::iterator curMap;
    bool dev = false;

    if(m_memoryMap.find(enemy) != m_memoryMap.end()) {
        curMap = m_memoryMap.find(enemy);
        dev = curMap->second.sensed;
    }

    return dev;
}

bool SensoryMemory::isAnyStrange(ARCS::Entity* enemy){
    std::map<ARCS::Entity*, MemoryRecord>::iterator curMap;
    bool dev = false;

    if(m_memoryMap.find(enemy) != m_memoryMap.end()) {
        curMap = m_memoryMap.find(enemy);
        dev = curMap->second.anyStrange;
    }

    return dev;
}

void SensoryMemory::setAnyStrange(ARCS::Entity* enemy){
    std::map<ARCS::Entity*, MemoryRecord>::iterator curMap;

    if(m_memoryMap.find(enemy) != m_memoryMap.end()) {
        curMap = m_memoryMap.find(enemy);
        curMap->second.anyStrange = true;
    }

}

void SensoryMemory::registEnt2React(ARCS::Entity &ent){
    ent2React.push_back(ent);
}

void SensoryMemory::check2React(ARCS::Entity& enemy, ARCS::CollisionSystem& colsys){
//Check if any object to react is ok
    if(isAnyStrange(&enemy)){
        for(auto& e : ent2React){
            if((!e.col || e.col->boxRoot.box.vertex1.x == 0) &&  colsys.checkObjectCollision(enemy.col->boxRoot,e.col->boxRoot, enemy.pos->position, e.pos->position)){
                setAnyStrange(&enemy);
                enemy.phy->normalSpeed += 1.5;
            }
        }
    }
}