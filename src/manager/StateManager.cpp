#include "StateManager.hpp"
#include <facade/Render/ManFacadeRender.hpp>
#include <facade/Sound/ManFacadeSound.hpp>
#include <string>


namespace ARCS {



StateManager::StateManager() {

    // Instance all game sounds
    auto* facade { ManFacadeSound::GetInstance()->getFacade() };

    // Effects
    facade->instanceEvent("event:/Efectos/sword hit", "");
    facade->instanceEvent("event:/Efectos/alarm", "");
    facade->instanceEvent("event:/Efectos/take_beer", "");
    facade->instanceEvent("event:/Efectos/take_key", "");
    facade->instanceEvent("event:/Efectos/take_money", "");
    facade->instanceEvent("event:/Efectos/fall_on_water", "");
    facade->instanceEvent("event:/Efectos/lever", "");
    facade->instanceEvent("event:/Efectos/atack_main", "");
    facade->instanceEvent("event:/Efectos/recover_health", "");
    facade->instanceEvent("event:/Efectos/orb", "");
    facade->instanceEvent("event:/Efectos/door", "");
    facade->instanceEvent("event:/Efectos/bearTrap", "");

    // Menu
    facade->instanceEvent("event:/Menús/Enter", "");
    facade->instanceEvent("event:/Menús/Options", "");
    facade->instanceEvent("event:/Menús/Pause", "");
    facade->instanceEvent("event:/Menús/Start_game", "");

    // Environments
    facade->instanceEvent("event:/Ambientes/storm", "");
    facade->instanceEvent("event:/Ambientes/surf", "");
    facade->instanceEvent("event:/Ambiente/village", "");
    facade->instanceEvent("event:/Ambientes/forest 2", "");
    facade->instanceEvent("event:/Ambientes/forest", "");
    facade->instanceEvent("event:/Ambientes/cave", "");

    // Music
    facade->instanceEvent("event:/Musica/Credits", "");
    facade->instanceEvent("event:/Musica/Level", "");
    facade->instanceEvent("event:/Musica/Level 2", "");
    facade->instanceEvent("event:/Musica/Level 3", "");
    facade->instanceEvent("event:/Musica/Level 4", "");
    facade->instanceEvent("event:/Musica/Soundtrack_Inicio", "");
    
    // Voices
    facade->instanceEvent("event:/Voces/Masculinas/hurt_enemy_men", "Hurt");
    facade->instanceEvent("event:/Voces/Masculinas/iSeeU", "");
    facade->instanceEvent("event:/Voces/Masculinas/iHeardSomething", "");
    facade->instanceEvent("event:/Voces/hurt_main", "Hurt");
    facade->instanceEvent("event:/Voces/Femeninas/hurt_enemy_women", "");
    facade->instanceEvent("event:/Voces/Femeninas/iHeardSomething", "");
    facade->instanceEvent("event:/Voces/Femeninas/iSeeU", "");
    facade->instanceEvent("event:/Voces/Femeninas/singing", "");
    facade->instanceEvent("event:/Voces/Masculinas/singing", "");
    facade->instanceEvent("event:/Voces/Masculinas/overHere", "");
    facade->instanceEvent("event:/Voces/hurt_main_women", "");
    facade->instanceEvent("event:/Voces/NPC/oldWoman", "");
    facade->instanceEvent("event:/Voces/NPC/villager", "");
    facade->instanceEvent("event:/Voces/NPC/prisoner", "");
    facade->instanceEvent("event:/Voces/NPC/prisonerSafe", "");
    facade->instanceEvent("event:/Voces/NPC/speedTrainer", "");
    facade->instanceEvent("event:/Voces/NPC/attackTrainer", "");
    facade->instanceEvent("event:/Voces/NPC/stealthTrainer", "");
    facade->instanceEvent("event:/Voces/danger", "");
    facade->instanceEvent("event:/Voces/safe", "");
    facade->instanceEvent("event:/Voces/phrase1Level1", "");
    facade->instanceEvent("event:/Voces/phrase2Level1", "");
    facade->instanceEvent("event:/Voces/phrase3Level1", "");

    facade->changeParameter(1, KeySound::Voces_Masculinas_hurt_enemy_men);
    facade->changeParameter(1, KeySound::Voces_hurt_main);

}



void
StateManager::update(float delta) {

    // Display game fps
    auto fps { fpsTimer.currentFPS() };
    if ( fps > -1 )
        ManFacadeRender::GetInstance()->getFacade()->setWindowTitle("VikinGO - " + std::to_string(fps) + " FPS");

    // Update current game state
    auto& state { m_States.top() };
    if(state && state->alive())
        state->update(delta);
    else
        m_States.pop();
}

bool
StateManager::alive() {
    return !m_States.empty();
}



} // namespace ECS