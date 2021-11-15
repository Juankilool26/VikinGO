#pragma once

#include <components/Box.hpp>
#include <glm/vec2.hpp>

namespace ARCS {


struct GameContext;
struct CollisionSystem;


class HealthSystem {
    
public:
    explicit HealthSystem(const ARCS::CollisionSystem &);
    bool update(GameContext& ) const;

private:
    bool leafNodeCollided(const BoundingBoxNode &) const;
    void startDamageSound(Entity *) const;
    float adjustRadians(float ) const;
    void calculateOrientation(Entity *,Entity *) const;
    void calculateLife(HealthComponent&) const;

    const CollisionSystem &colsys;

};


} // namespace ARCS