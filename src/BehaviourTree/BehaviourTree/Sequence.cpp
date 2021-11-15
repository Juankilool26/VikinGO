#include "Sequence.hpp"


Sequence::~Sequence() {

}


bool
Sequence::run(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map)
{
    for (Node* child : getChildren()) 
    {  
        if (child && !child->run(mr, arr, pos, ai, wp, map)) 
            return false;
    }
    return true;  
}