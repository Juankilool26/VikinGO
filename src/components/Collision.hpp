#pragma once

#include <cstdint>
#include <components/Component.hpp>
#include "Box.hpp"


namespace ARCS {


struct CollisionComponent : public Component {
    explicit CollisionComponent(int entID) 
        : Component { entID }
    { };


    enum {
        L_NoLayer  = 0b00000000,
        L_Obstacle = 0b00000001,
        L_Item     = 0b00000010,
        L_Enemy    = 0b00000100,
        L_AllLayer = 0b11111111
    };

    enum {
        P_Nothing  = 0b00000000,
        P_IsPlayer = 0b00000001,
        P_IsEnemy  = 0b00000010,
        P_IsSolid  = 0b00000100,
        P_Damages  = 0b00001000     // f.e. Traps
    };


    uint8_t properties { P_Nothing };
    uint8_t mask { L_AllLayer };
    BoundingBoxNode boxRoot { };
};


} // namespace ARCS