#pragma once

#include "Node.hpp"



struct Decorator : Node
{
    virtual ~Decorator();
    const Node* getChild() const;
    void addChild (Node *);

protected:
    Node* child;

};
