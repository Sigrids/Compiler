#pragma once
#ifndef CODE_H
#define CODE_H

#include <sstream>
#include "tree.h"
#include "scope.h"
 
class Code
{
public:
	Code(Tree*);
	std::string getCode();
	void generate();
private:
    Tree* pTree;
	Scope scope;
	int tempCount;
	int labelCount;
	std::ostringstream asmCode;
	std::string getNewTemp();
	std::string getNewLabel();
	void gen_Program(Tree*);
	void gen_Block(Tree*);
	void gen_Vars(Tree*);
	void gen_Expr(Tree*);
	void gen_A(Tree*);
	void gen_N(Tree*);
	void gen_M(Tree*);
	void gen_R(Tree*);
	void gen_Stats(Tree*);
	void gen_Mstat(Tree*);
	void gen_Stat(Tree*);
	void gen_In(Tree*);
	void gen_Out(Tree*);
	void gen_If(Tree*);
	void gen_Loop(Tree*);
	void gen_Assign(Tree*);
	void gen_RO(Tree*, std::string);
};

#endif /* CODE_H */
