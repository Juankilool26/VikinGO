#pragma once

#include <components/Box.hpp>

namespace ARCS {


struct GameContext;
struct PositionComponent;
struct CollisionComponent;



struct CollisionSystem {
    
    
public:
    explicit CollisionSystem() = default;
    bool update(GameContext &) const noexcept;
    bool checkObjectCollision(BoundingBoxNode &,BoundingBoxNode &,const glm::vec3 &,const glm::vec3 &) const noexcept;
    bool checkBetween(BoundingBoxNode &, BoundingBoxNode &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &) const noexcept;

private:
    BoundingBox move2WorldCoords(const BoundingBox &, const glm::vec3 &) const noexcept;
    void react2Collision(GameContext &,CollisionComponent &,CollisionComponent &) const noexcept;
    void undoCollision(GameContext &,CollisionComponent &,CollisionComponent &) const noexcept;

};


} // namespace ARCS