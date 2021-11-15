#include "BehaviorRecord.hpp"


namespace SCH {




BehaviorRecord::BehaviorRecord(UPNode action, unsigned int frec, unsigned int ph)
    :   node { std::move(action) }
    ,   frequency { frec }
    ,   phase { ph }
{ }




} // namespace SCH