#pragma once

#include "Node.hpp"

struct Composite : Node //This is a node that contains other nodes or leafs
{
	virtual ~Composite();
	const std::list<Node*>& getChildren() const;
	void addChild (Node *);

private:
	std::list<Node*> children;
 
};
