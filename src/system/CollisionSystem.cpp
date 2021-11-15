#include <glm/glm.hpp>
#include <manager/GameContext.hpp>
#include <TriggerSystem/TriggerSystem.hpp>
#include <functional>
#include <math.h>
#include "CollisionSystem.hpp"




namespace ARCS {




bool
CollisionSystem::update(GameContext& gc) const noexcept {
    auto& ColCmpVec { gc.getCollisionComponents() };
    
    // Dont collide at the beginning
    std::function<void(BoundingBoxNode&)> falseAllCollides =
        [&](BoundingBoxNode& box) {
            box.collided = false;
            for (auto& b : box.childs) falseAllCollides(b);
        };
    for (auto& cmp : ColCmpVec) falseAllCollides(cmp.boxRoot);


    for (std::size_t i=0; i<ColCmpVec.size(); ++i) {
        auto& c1 { ColCmpVec[i] };
        const auto* pos1 = gc.getPositionComponentByID( c1.getEntityID() );
        if (!pos1) continue;
        if (!gc.getEntityById(pos1->getEntityID())->sens) continue;

        for (std::size_t j=i+1; j<ColCmpVec.size(); ++j) {
            auto& c2 { ColCmpVec[j] };
            if ( (c1.mask & c2.mask) == 0 ) continue;
            const auto* pos2 = gc.getPositionComponentByID( c2.getEntityID() );
            if (!pos2) continue;
            if ( checkObjectCollision(c1.boxRoot, c2.boxRoot, pos1->position, pos2->position) )
                react2Collision(gc, c1, c2);
        }

        
    }

    return true;
}



bool
CollisionSystem::checkObjectCollision(BoundingBoxNode &bn1, BoundingBoxNode &bn2, const glm::vec3 &pos1, const glm::vec3 &pos2) const noexcept {

    auto box1 = move2WorldCoords(bn1.box, pos1);
    auto box2 = move2WorldCoords(bn2.box, pos2);

    // AABB Collision
    if (    (box1.vertex1.x <= box2.vertex2.x  &&  box1.vertex2.x >= box2.vertex1.x)    &&
            (box1.vertex1.y <= box2.vertex2.y  &&  box1.vertex2.y >= box2.vertex1.y)    &&
            (box1.vertex1.z <= box2.vertex2.z  &&  box1.vertex2.z >= box2.vertex1.z)    )
    {

        // Search the leaves collided for each box node
        if ( bn1.childs.size() > 0 ) {
            for (auto& b : bn1.childs)
                if ( checkObjectCollision(b, bn2, pos1, pos2) ) return true;
        } else if ( bn2.childs.size() > 0 ) {
            for (auto& b : bn2.childs)
                if ( checkObjectCollision(bn1, b, pos1, pos2) ) return true;
        } else {
            bn1.collided = true;
            bn2.collided = true;
            return true;
        }
    }

    return false;
}

bool
CollisionSystem::checkBetween(BoundingBoxNode &bn1, BoundingBoxNode &bn2, const glm::vec3 &pos1, const glm::vec3 &pos2, const glm::vec3 &pos3) const noexcept {

    // Check distance object and player
    if (sqrt(pow(std::abs(pos1.x - pos2.x),2) + pow(std::abs(pos1.z - pos2.z),2))
         < sqrt(pow(std::abs(pos1.x - pos3.x),2) + pow(std::abs(pos1.z - pos3.z),2))  )
    {
        
        return checkObjectCollision(bn1,bn2,pos1,pos2);
    }

    return false;
}




BoundingBox
CollisionSystem::move2WorldCoords(const BoundingBox &boundingBox, const glm::vec3 &pos) const noexcept {
    BoundingBox worldBox {
        pos + boundingBox.vertex1,
        pos + boundingBox.vertex2
    };
    return worldBox;
}






void
CollisionSystem::undoCollision(GameContext& gc, CollisionComponent& col1, CollisionComponent& col2) const noexcept {

    PositionComponent* poscmp1 { gc.getPositionComponentByID( col1.getEntityID() ) };
    PositionComponent* poscmp2 { gc.getPositionComponentByID( col2.getEntityID() ) };

    auto box1 { move2WorldCoords(col1.boxRoot.box, poscmp1->position) };
    auto box2 { move2WorldCoords(col2.boxRoot.box, poscmp2->position) };

    // Calculates intersection in 1-D
    auto intervalIntersection = [](float B1l, float B1r, float B2l, float B2r) -> float {
        if (B1l < B2l) {
            if (B1r < B2r)    return B2l - B1r;
        } else if (B1r > B2r) return B2r - B1l;
        return 0;
    };

    struct { float x, z; } overlap {
        intervalIntersection(box1.vertex1.x, box1.vertex2.x, box2.vertex1.x, box2.vertex2.x),
        intervalIntersection(box1.vertex1.z, box1.vertex2.z, box2.vertex1.z, box2.vertex2.z)
    };

    // Undo overlap movement
    if (overlap.x == 0  ||  (overlap.z != 0 && glm::abs(overlap.z) < glm::abs(overlap.x)))
        poscmp1->position.z += (overlap.z < 0) ? overlap.z-0.001f : overlap.z+0.01f;
    else
        poscmp1->position.x += (overlap.x < 0) ? overlap.x-0.001f : overlap.x+0.01f;

}






void
CollisionSystem::react2Collision(GameContext& gc, CollisionComponent& col1, CollisionComponent& col2) const noexcept {

    auto BoxIsSolid = [](CollisionComponent& col) -> bool {
        return (col.properties & CollisionComponent::P_IsSolid);
    };

    auto BoxIsEnemy = [](CollisionComponent& col) -> bool {
        return (col.properties & CollisionComponent::P_IsEnemy);
    };

    auto BoxIsPlayer = [](CollisionComponent& col) -> bool {
        return (col.properties & CollisionComponent::P_IsPlayer);
    };

    auto BoxIsAlive = [&](CollisionComponent& col) -> bool {
        return (BoxIsEnemy(col) || BoxIsPlayer(col));
    };


    CollisionComponent* c1 { &col1 };
    CollisionComponent* c2 { &col2 };

    if ( BoxIsAlive(col2) ) std::swap(c1, c2);
    else if ( BoxIsSolid(col1) ) return;

    //if (BoxIsPlayer(*c1)  &&  BoxIsEnemy(*c2)) std::swap(c1, c2); // FIXED: Dont empootar player

    undoCollision(gc, col1, col2);

}






} // namespace ARCS