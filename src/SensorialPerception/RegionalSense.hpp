#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include <components/Box.hpp>
#include <components/Position.hpp>

struct Vision {
    glm::vec3 positionRelative { };
    ARCS::BoundingBoxNode boxRootSup;
    ARCS::BoundingBoxNode boxRootInf;
};

struct RegionalSense {
    Vision vision;
    ARCS::BoundingBoxNode hearing;
    ARCS::BoundingBoxNode noise;
};


// Composite Pattern
