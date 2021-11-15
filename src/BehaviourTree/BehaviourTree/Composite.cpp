#include "Composite.hpp"



Composite::~Composite() {
    children.clear();
}


const std::list<Node*>&
Composite::getChildren() const {
    return children;
}


void
Composite::addChild (Node* child) {
    children.emplace_back(child);
}