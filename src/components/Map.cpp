#include "Map.hpp"
#include "glm/glm.hpp"


void
MapComponent::addKeyPoint(glm::vec3&& point) {
    keyPoints.insert({ ++idZone, point });
}

void
MapComponent::addAuxPoint(glm::vec3&& point) {
    auxPoints.insert({ ++idZoneAux, point });
}


unsigned int
MapComponent::getClosestKeyPoint(const glm::vec3& point) const noexcept {
    unsigned int closestID { 0 };
    float closestDistance { 0.0f };

    for (auto& [id, pt] : keyPoints) {
        float distance { glm::distance(point, pt) };
        if ((closestDistance == 0.0f  ||  closestDistance > distance) && distance > 0) {
            closestDistance = distance;
            closestID = id;
        }
    }
    return closestID;
}

unsigned int
MapComponent::getClosestAuxPoint(const glm::vec3& point) const noexcept {
    unsigned int closestID { 0 };
    float closestDistance { 0.0f };

    for (auto& [id, pt] : auxPoints) {
        float distance { glm::distance(point, pt) };
        if ((closestDistance == 0.0f  ||  closestDistance > distance) && distance > 0) {
            closestDistance = distance;
            closestID = id;
        }
    }
    return closestID;
}


glm::vec3
MapComponent::getKeyPointByID(unsigned int id) const noexcept {
    auto it = keyPoints.find(id);
    if ( it != keyPoints.end() )
        return it->second;
    return { };
}

glm::vec3
MapComponent::getAuxPointByID(unsigned int id) const noexcept {
    auto it = auxPoints.find(id);
    if ( it != auxPoints.end() )
        return it->second;
    return { };
}