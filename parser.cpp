#include <iostream>
#include "token.h"
#include "parser.h"
#include "input.h"
#include "tree.h"


void printTokenList(std::vector<Token>);
void printTree(Tree*, int);

Tree* parser(int args, char** arg) {
	FILE* f = getfp(args, arg);
	std::string str,print;
	std::vector<Token> tokenList;
	while (!feof(f)){
		str = next(f);
		Token tk = scanner(str);
		tokenList.push_back(tk);
		}
	Tree *root = Tree::tree_program(tokenList);
	return root;
}

void printTokenList(std::vector<Token> list)
{
	std::cout << "--Token List:--\n";
	for (int i = 0; i < list.size(); i++){
		std::cout << list[i].getTokenEnum().toString() << ": " << list[i].getTokenStr() << "\n";
	}
}

void printTree(Tree* node, int tab_lvl){
	int i = 0;
	while (i <= tab_lvl - 1){
		std::cout << "_ ";
		i++;
	}
	if (node->node_name == "end"){
		if (node->token->getTokenEnum() == TokenEnum::id_tk){
			std::cout << "Id: " << node->token->getTokenStr() << "\n";
		}
		else if (node->token->getTokenEnum() == TokenEnum::int_tk){
			std::cout << "int: " << node->token->getTokenStr() << "\n";
		}
		else{
			std::cout << "<" << node->node_name << ">\n";
		}
	}
	else{
		std::cout << "<" << node->node_name << ">\n";
	}
	tab_lvl++;
	if (node->child1 != NULL) printTree(node->child1, tab_lvl);
	if (node->child2 != NULL) printTree(node->child2, tab_lvl);
	if (node->child3 != NULL) printTree(node->child3, tab_lvl);
	if (node->child4 != NULL) printTree(node->child4, tab_lvl);
}
