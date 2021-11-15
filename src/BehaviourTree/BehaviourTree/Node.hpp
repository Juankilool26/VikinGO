#pragma once

#include <list>
#include <vector>
#include <cmath>
#include <RecordMemory/MemoryRecord.hpp>
#include <components/Weapon.hpp>
#include <components/AI.hpp>
#include <components/Position.hpp>
#include <components/Map.hpp>
#include <components/Arrow.hpp>


struct Node
{
	virtual ~Node() = default;
	virtual bool run(MemoryRecord&,ARCS::ArrowComponent&,ARCS::PositionComponent&,ARCS::AIComponent&,ARCS::WeaponComponent&,MapComponent&) = 0;
}; 
