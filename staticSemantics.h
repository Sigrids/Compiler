#pragma once
#ifndef STATICSEMANTICS_H
#define STATICSEMANTICS_H

#include <vector>
#include <string>
#include "tree.h"

class StaticSemantics
{
public:
	StaticSemantics();
	StaticSemantics(Tree*);
	void loadTree(Tree*);
	void checkTree();

private:
	Tree* tree;
	void travel(Tree*, std::vector<std::string>&, std::vector<std::string>&);
};

#endif /* STATICSEMANTICS_H */

