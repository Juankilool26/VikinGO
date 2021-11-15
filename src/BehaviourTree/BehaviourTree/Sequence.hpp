#pragma once

#include "Composite.hpp"

struct Sequence : Composite //All the childs need to succeed (in order)
{ 
	~Sequence();
	bool run(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map) override;
}; 
