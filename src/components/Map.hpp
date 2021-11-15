#pragma once

#include <map>
#include <glm/vec3.hpp>
#include "Component.hpp"


struct MapComponent {

    explicit MapComponent() = default;
    void addKeyPoint(glm::vec3 &&);
    unsigned int getClosestKeyPoint(const glm::vec3 &) const noexcept;
    glm::vec3 getKeyPointByID(unsigned int ) const noexcept;
    void addAuxPoint(glm::vec3 &&);
    unsigned int getClosestAuxPoint(const glm::vec3 &) const noexcept;
    glm::vec3 getAuxPointByID(unsigned int ) const noexcept;

    unsigned int idZone { 0 };
    unsigned int idZoneAux { 0 };
    std::map<unsigned int, glm::vec3> keyPoints { };
    std::map<unsigned int, glm::vec3> auxPoints { };
  
};