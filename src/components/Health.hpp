#pragma once

#include <components/Component.hpp>


namespace ARCS {


struct HealthComponent : public Component {
    explicit HealthComponent(int entID) 
        : Component { entID }
    { };

    int health { 1 };
    inline static int maxHP { 6 };
};


} // namespace ARCS