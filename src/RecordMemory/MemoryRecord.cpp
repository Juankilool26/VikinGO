#include "MemoryRecord.hpp"



bool
MemoryRecord::isMemoryEmpty() const {
    return ( withinFOV  &&  !sensed );
}