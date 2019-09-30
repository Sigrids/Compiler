#include <iostream>
#include "code.h"
#include "tree.h"
#include "scope.h"

int findS(std::vector<std::string> varStack, std::string str)
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

Code::Code(Tree* tree)
{
	pTree = tree;
	tempCount = 0;
	labelCount = 0;
}

std::string Code::getCode()
{
	return asmCode.str();
}

std::string Code::getNewTemp()
{
	tempCount++;
	return "T" + std::to_string(tempCount);
}

std::string Code::getNewLabel()
{
	labelCount++;
	return "L" + std::to_string(labelCount);
}

void Code::generate()
{
	gen_Program(pTree);
	asmCode << "\n";
	for (int i = 1; i <= tempCount; i++)
	{
		asmCode << "T" << i << " 0\n";
	}
}

void Code::gen_Program(Tree* node)
{
	int startCount = scope.getCount();
	if (node->child1 != NULL)
	{
		gen_Vars(node->child1);
	}
	gen_Block(node->child2);

	for (int i = scope.getCount() - 1; i >= startCount; i--)
	{
		scope.pop();
		asmCode << "POP\n";
	}

	asmCode << "STOP\n";
}

void Code::gen_Block(Tree* node)
{
	int startCount = scope.getCount();
	if (node->child1 != NULL)
	{
		gen_Vars(node->child1);
	}

	gen_Stats(node->child2);

	for (int i = scope.getCount() - 1; i >= startCount; i--)
	{
		scope.pop();
		asmCode << "POP\n";
	}
}

void Code::gen_Vars(Tree* node)
{
	scope.push(node->child1->token->getTokenStr());
	asmCode << "PUSH\n";

	if (node->child3 != NULL)
	{
		gen_Vars(node->child3);
	}
}

void Code::gen_Expr(Tree* node)
{
	if (node->token == NULL)
	{
		gen_A(node->child1);
	}
	else
	{
		gen_Expr(node->child2);
		std::string temp = getNewTemp();
		asmCode << "STORE " << temp << "\n";
		gen_A(node->child1);

		if (node->token->getTokenEnum() == TokenEnum::plus_tk)
		{
			asmCode << "ADD " << temp << "\n";
		}
		else if (node->token->getTokenEnum() == TokenEnum::minus_tk)
		{
			asmCode << "SUB " << temp << "\n";
		}
	}
}

void Code::gen_A(Tree* node)
{
	if (node->token == NULL)
	{
		gen_N(node->child1);
	}
	else
	{
		gen_A(node->child2);
		std::string temp = getNewTemp();
		asmCode << "STORE " << temp << "\n";
		gen_N(node->child1);
		asmCode << "DIV " << temp << "\n";
	}
}

void Code::gen_N(Tree* node)
{
	if (node->token == NULL)
	{
		gen_M(node->child1);
	}
	else
	{
		gen_N(node->child2);
		std::string temp = getNewTemp();
		asmCode << "STORE " << temp << "\n";
		gen_M(node->child1);
		asmCode << "MULT " << temp << "\n";
	}
}

void Code::gen_M(Tree* node)
{
	if (node->token == NULL)
	{
		gen_R(node->child1);
	}
	else if (node->token->getTokenEnum() == TokenEnum::pct_tk)
	{
		gen_M(node->child1);
		asmCode << "MULT -1\n";
	}
}

void Code::gen_R(Tree* node)
{
	if (node->child1->node_name == "expr")
	{
		gen_Expr(node->child1);
	}
	else if (node->child1->token->getTokenEnum() == TokenEnum::id_tk)
	{
		// LOAD ID
		asmCode << "STACKR " << scope.find(node->child1->token->getTokenStr()) << std::endl;
	}
	else if (node->child1->token->getTokenEnum() == TokenEnum::int_tk)
	{
		// LOAD VAR
		asmCode << "LOAD " << node->child1->token->getTokenStr() << "\n";
	}
}

void Code::gen_Stats(Tree* node)
{
	gen_Stat(node->child1);
	gen_Mstat(node->child2);
}

void Code::gen_Mstat(Tree* node)
{
	if (node != NULL)
	{
		gen_Stat(node->child1);
		gen_Mstat(node->child2);
	}
}

void Code::gen_Stat(Tree* node)
{
	if (node->child1->node_name == "in")
	{
		gen_In(node->child1);
	}
	else if (node->child1->node_name == "out")
	{
		gen_Out(node->child1);
	}
	else if (node->child1->node_name == "block")
	{
		gen_Block(node->child1);
	}
	else if (node->child1->node_name == "if")
	{
		gen_If(node->child1);
	}
	else if (node->child1->node_name == "loop")
	{
		gen_Loop(node->child1);
	}
	else if (node->child1->node_name == "assign")
	{
		gen_Assign(node->child1);
	}
}

void Code::gen_In(Tree* node)
{
	std::string temp = getNewTemp();
	asmCode << "READ " << temp << "\n";
	asmCode << "LOAD " << temp << "\n";
	asmCode << "STACKW " << scope.find(node->child1->token->getTokenStr()) << "\n";
}

void Code::gen_Out(Tree* node)
{
	gen_Expr(node->child1);
	std::string temp = getNewTemp();
	asmCode << "STORE " << temp << "\n";
	asmCode << "WRITE " << temp << "\n";
}

void Code::gen_If(Tree* node)
{
	//sub child 1 from child 3
	gen_Expr(node->child3);
	std::string temp = getNewTemp();
	asmCode << "STORE " << temp << "\n";
	gen_Expr(node->child1);
	asmCode << "SUB " << temp << "\n";
	//create new label to set the condition
	std::string label = getNewLabel();
	gen_RO(node->child2, label);

	gen_Stat(node->child4);

	asmCode << label << ": NOOP\n";
}

void Code::gen_Loop(Tree* node)
{
	std::string label1 = getNewLabel();
	asmCode << label1 << ": NOOP\n";
	//sub child 1 from child 3
	gen_Expr(node->child3);
	std::string temp = getNewTemp();
	asmCode << "STORE " << temp << "\n";
	gen_Expr(node->child1);
	asmCode << "SUB " << temp << "\n";
	//create new label to set the condition
	std::string label2 = getNewLabel();

	gen_RO(node->child2, label2);
	gen_Stat(node->child4);

	asmCode << "BR " << label1 << "\n";
	asmCode << label2 << ": NOOP\n";
}

void Code::gen_Assign(Tree* node)
{
	gen_Expr(node->child2);
	asmCode << "STACKW " << scope.find(node->child1->token->getTokenStr()) << "\n";
}

void Code::gen_RO(Tree* node, std::string label)
{
	if (node->child1->token->getTokenEnum() == TokenEnum::lt_tk)
	{
		if (node->child2 != NULL && node->child2->token->getTokenEnum() == TokenEnum::lgt_tk)
		{
			asmCode << "BRZERO " << label << "\n";
		}
		else
		{
			asmCode << "BRZPOS " << label << "\n";
		}
	}
	else if (node->child1->token->getTokenEnum() == TokenEnum::eq_tk)
	{
		if (node->child2 != NULL && node->child2->token->getTokenEnum() == TokenEnum::lt_tk)
		{
			asmCode << "BRPOS " << label << "\n";
		}
		else if (node->child2 != NULL && node->child2->token->getTokenEnum() == TokenEnum::lgt_tk)
		{
			asmCode << "BRNEG " << label << "\n";
		}
		else
		{
			asmCode << "BRPOS " << label << "\n";
			asmCode << "BRNEG " << label << "\n";
		}
	}
	else if (node->child1->token->getTokenEnum() == TokenEnum::lgt_tk)
	{
		asmCode << "BRZNEG " << label << "\n";
	}
}
