#include <iostream>
#include <string>
#include <vector>
#include "exceptions.h"
#include "tree.h"
#include "staticSemantics.h"

int find(std::vector<std::string> varStack, std::string str)
{
	for (int i = varStack.size() - 1; i >= 0; i--)
	{
		if (varStack[i] == str)
		{
			return i;
		}
	}
	return -1;
}

void printStack(std::vector<std::string> varStack)
{
	std::cout << "Stack:\n";
	for (int i = varStack.size() - 1; i >= 0; i--)
	{
		std::cout << varStack[i] << "\n";
	}
	std::cout << "End Stack\n";
}

StaticSemantics::StaticSemantics()
{
	tree = NULL;
}

StaticSemantics::StaticSemantics(Tree* root)
{
	loadTree(root);
}

void StaticSemantics::loadTree(Tree* root)
{
	tree = root;
}

void StaticSemantics::checkTree()
{
	std::vector <std::string> localStack;
	std::vector <std::string> globalStack;
	travel(tree, localStack, globalStack);
}

void StaticSemantics::travel(Tree* node, std::vector<std::string>& localStack, std::vector<std::string>& globalStack)
{
	if (node == NULL)
	{
		return;
	}
	if (node->node_name == "program")
	{
		StaticSemantics::travel(node->child1, localStack, globalStack);
		StaticSemantics::travel(node->child2, localStack, globalStack);
	}
	else if (node->node_name == "block")
	{
		std::vector<std::string> blockLocalStack;
		std::vector<std::string> blockGlobalStack = globalStack;
		for (int i = 0; i < localStack.size(); i++)
		{
			blockGlobalStack.push_back(localStack[i]);
		}
		StaticSemantics::travel(node->child1, blockLocalStack, blockGlobalStack);
		StaticSemantics::travel(node->child2, blockLocalStack, blockGlobalStack);
	}
	else if (node->node_name == "R")
	{
		if (node->child1->node_name == "end")
		{
			if (node->child1->token->getTokenEnum() == TokenEnum::id_tk)
			{
				std::string var = node->child1->token->getTokenStr();
				//std::cout << var << "<-r\n";
				if (find(localStack, var) < 0 && find(globalStack, var) < 0)
				{
					std::cout << var << "\n";
					throw CompilerException("Var above not defined in END");
				}
			}
		}
		else
		{
			StaticSemantics::travel(node->child1, localStack, globalStack);
		}
	}
	else if (node->node_name == "in")
	{
		std::string var = node->child1->token->getTokenStr();
		if (find(localStack, var) < 0 && find(globalStack, var) < 0)
		{
			std::cout << var << "\n";
			throw CompilerException("Var above not defined in IN.");
		}
	}
	else if (node->node_name == "assign")
	{
		std::string var = node->child1->token->getTokenStr();
		if (find(localStack, var) < 0 && find(globalStack, var) < 0)
		{
			std::cout << var << "\n";
			throw CompilerException("Var above not defined in ASSIGN");
		}
		StaticSemantics::travel(node->child2, localStack, globalStack);
	}
	else if (node->node_name == "vars")
        {
                std::string var = node->child1->token->getTokenStr();
                if (find(localStack, var) >= 0)
                {
                        std::cout << var << "\n";
                        throw CompilerException("Var above already defined in VARS.");
                }
                localStack.push_back(var);
                StaticSemantics::travel(node->child3, localStack, globalStack);
        }
	else
	{
		if (node->child1 != NULL) StaticSemantics::travel(node->child1, localStack, globalStack);
		if (node->child2 != NULL) StaticSemantics::travel(node->child2, localStack, globalStack);
		if (node->child3 != NULL) StaticSemantics::travel(node->child3, localStack, globalStack);
		if (node->child4 != NULL) StaticSemantics::travel(node->child4, localStack, globalStack);
	}
}
