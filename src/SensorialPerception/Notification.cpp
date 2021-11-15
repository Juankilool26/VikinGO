#include "Notification.hpp"


Notification::Notification(ARCS::Entity &receiveEn, RegionalSense &receiveRsense, ARCS::BoundingBoxNode &receiveNoise,ARCS::BoundingBoxNode &receiveBody, glm::vec3 &receivePos, glm::vec3 &receivePosEn)
    : en{receiveEn}, rSense{receiveRsense}, noise{receiveNoise}, body{receiveBody}, pos{receivePos}, posEn{receivePosEn}
{ }