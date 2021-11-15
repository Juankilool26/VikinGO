#pragma once

#include <components/Entity.hpp>
#include <system/CollisionSystem.hpp>

namespace ARCS{
    struct GameContext;
}

class Trigger
{

public:
    explicit Trigger(int eid);
    virtual ~Trigger() = default;
    virtual bool Try(ARCS::GameContext&, ARCS::CollisionSystem&, float) = 0;
    virtual void Update(float) = 0;
    bool isToBeRemoved() const {return remove;}
    bool isActive() const {return active;}
    void setActive(){active = true;}
    void setInactive(){active = false;}

    int id { ++nextID };
    int entID;
    ARCS::BoundingBoxNode boxRootRangeTrigger;

protected:
    void setToBeRemoved(){remove = true;}
    bool intersects(ARCS::CollisionSystem& cs, glm::vec3 pos, ARCS::Entity& player);

    static float animationSpeed;

private:
    bool remove = false;
    bool active = true;
    inline static int nextID { 0 };

        
};