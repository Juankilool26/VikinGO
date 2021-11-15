#include "WeaponSystem.hpp"
#include <manager/GameContext.hpp>




namespace ARCS {



bool
WeaponSystem::update(GameContext& gc, float delta) const noexcept
{
    auto& weapons = gc.getWeaponComponents();
    for(auto& weapon : weapons)
    {

        auto* ent = gc.getEntityById(weapon.getEntityID());
        if ( !ent  ||  !ent->heal  ||  !ent->heal->health ) continue;
        
        if ( weapon.hiting  &&  weapon.time2HitAgain >= weapon.limitTime4Waiting ) {

            if ( weapon.displacement < weapon.limitDistance4Attacking ) {

                float displacementX { 0.0f };
                float displacementZ { 0.0f };

                // Get player or enemy direction
                if ( ent->ai ) {
                    displacementX = ent->phy->speedDisplacementVector.x;
                    displacementZ = ent->phy->speedDisplacementVector.z;
                } else {
                    auto* cam = gc.getEntityById(gc.getCameraComponents()[0].getEntityID());
                    displacementX = cam->cam->direction.x;
                    displacementZ = cam->cam->direction.z;
                }

                displacementX *= delta * weapon.velocity;
                displacementZ *= delta * weapon.velocity;

                weapon.displacement += glm::sqrt( glm::pow(displacementX, 2) + glm::pow(displacementZ, 2) );

                // Update weapon displacement
                weapon.wpositionRelative.x += displacementX;
                weapon.wpositionRelative.z += displacementZ;

            } else if ( weapon.displacement >= weapon.limitDistance4Attacking ) {

                weapon.wpositionRelative.x = weapon.wpositionRelative.z = 0;
                weapon.time2HitAgain = weapon.displacement = 0;
                //if ( ent->inp ) 
                weapon.hiting = false;
                
            }

        } else {

            weapon.time2HitAgain += delta;
            weapon.wpositionRelative.x = weapon.wpositionRelative.z = weapon.displacement = 0;

        }

    }
    return true;
}





} // namespace ARCS