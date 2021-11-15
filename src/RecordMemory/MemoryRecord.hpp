#pragma once
#include <glm/vec3.hpp>
#include <chrono>


struct MemoryRecord {
    float timeLastSensed;          //ultima vez que el enemigo sintio al personaje
    float timeBecameVisible;       //momento en el que empezo a ser visible
    float timeLastVisible;         //ultimo momneto en el que fue visto
    glm::vec3 lastSensePosition;    //guardar posicion de ultima vez que fue sentido
    bool withinFOV = true;          //es true si el personaje no esta en campo de vision
    bool hittable = false;          //es true si no hay obstaculo entre enemigo-personaje
    bool sensed = false;
    bool anyStrange = false;
    bool isMemoryEmpty() const;
};
