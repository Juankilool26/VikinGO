#pragma once

#include <vector>
#include <glm/vec3.hpp>

namespace ARCS {


struct BoundingBox {
    glm::vec3 vertex1 { }, vertex2 { };
};

struct BoundingBoxNode {
    BoundingBox box { };
    bool collided { false };
    std::vector<BoundingBoxNode> childs { };
};

// Composite Pattern


} // namespace ARCS