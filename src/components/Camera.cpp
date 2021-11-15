#include <glm/glm.hpp>
#include "Camera.hpp"


namespace ARCS {

CameraComponent::CameraComponent(int entID)
    : Component ( entID )
{ }

float
CameraComponent::getRelativeDistance() {
    return distanceRelative;
}

void
CameraComponent::calculateRelativeDistance(const glm::vec3& pCam, const glm::vec3& pNode) {
    distanceRelative = glm::distance(pCam, pNode);
}

} // namespace ARCS