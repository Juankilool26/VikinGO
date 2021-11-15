#pragma once

#include <string_view>
#include <manager/EntityManager.hpp>


struct GameObjectFactory {
    explicit GameObjectFactory(ARCS::EntityManager &);

    GameObjectFactory(const GameObjectFactory&) = delete;
    GameObjectFactory(GameObjectFactory&&) = delete;
    GameObjectFactory& operator=(const GameObjectFactory&) = delete;
    GameObjectFactory& operator=(GameObjectFactory&&) = delete;
    
    ARCS::Entity& loadLevelJSON(std::string_view, int, MapComponent&) const;

    ARCS::Entity& createPlayer(glm::vec3, glm::vec3, std::string, int, float, float, glm::vec3, glm::vec3) const;
    ARCS::Entity& createEnemy(glm::vec3, glm::vec3, std::string, int, glm::vec3, glm::vec3) const;
    ARCS::Entity& createArcher(glm::vec3 ,glm::vec3 ,std::string_view ,unsigned int ,unsigned int ) const;
    ARCS::Entity& createMannequin(glm::vec3, glm::vec3, std::string, int, glm::vec3, glm::vec3) const;
    ARCS::Entity& createObject(glm::vec3, glm::vec3, std::string, glm::vec3, glm::vec3) const;
    ARCS::Entity& createCamera(ARCS::Entity &, glm::vec3, glm::vec3) const;
    ARCS::Entity& createCollider(glm::vec3, glm::vec3, glm::vec3, glm::vec3) const;


private:
    ARCS::EntityManager& EntMan;
    ARCS::Entity& createEntityObject(glm::vec3 ,glm::vec3 ,std::string_view ) const;
    SCH::FrequencyScheduler createArcherScheduler(unsigned int ,unsigned int ) const;
};
