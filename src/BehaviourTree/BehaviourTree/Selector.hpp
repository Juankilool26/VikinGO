#pragma once

#include "Composite.hpp"

struct Selector : Composite //Only one child needs to succeed
{ 
	~Selector();
	bool run(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map) override;
};
