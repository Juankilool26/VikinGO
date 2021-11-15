#include "Decorator.hpp"



Decorator::~Decorator() {
    child = nullptr;
}


const Node*
Decorator::getChild() const {
    return child;
}




void
Decorator::addChild(Node* node) {
    child = node;
}