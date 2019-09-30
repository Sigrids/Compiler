
#ifndef TREE_H
#define TREE_H

#include <vector>
#include "token.h"


class Tree
{
public:
	Tree();
	Token* token;
	int loc;
	std::string node_name;
	Tree* child1;
	Tree* child2;
	Tree* child3;
	Tree* child4;
	static Tree* tree_end(std::vector<Token>&);
	static void defNode(Tree*, std::vector<Token>&);
	static Tree* tree_program(std::vector<Token>&);
	static Tree* tree_block(std::vector<Token>&);
	static Tree* tree_vars(std::vector<Token>&);
	static Tree* tree_expr(std::vector<Token>&);
	static Tree* tree_A(std::vector<Token>&);
	static Tree* tree_N(std::vector<Token>&);
	static Tree* tree_M(std::vector<Token>&);
	static Tree* tree_R(std::vector<Token>&);
	static Tree* tree_stats(std::vector<Token>&);
	static Tree* tree_mStat(std::vector<Token>&);
	static Tree* tree_stat(std::vector<Token>&);
	static Tree* tree_in(std::vector<Token>&);
	static Tree* tree_out(std::vector<Token>&);
	static Tree* tree_if(std::vector<Token>&);
	static Tree* tree_loop(std::vector<Token>&);
	static Tree* tree_assign(std::vector<Token>&);
	static Tree* tree_RO(std::vector<Token>&);
private:
	static void check_eof(std::vector<Token>);

};




#endif // TREE_H