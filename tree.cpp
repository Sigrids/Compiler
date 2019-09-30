#include <iostream>
#include <string>
#include <vector>
#include "exceptions.h"
#include "tree.h"


Tree::Tree() {
	token = NULL;
	loc = 0;
	node_name = "root";
	child1 = NULL;
	child2 = NULL;
	child3 = NULL;
	child4 = NULL;
}

Tree* nul = new Tree;
int loc_cntr = 0;

Tree* Tree::tree_end(std::vector<Token>&list) 
{
	Tree* nul = new Tree;
	if (list.size() <= 0) {
		throw CompilerException("Unecpected EOF\n");
	}
	if(list.front().getTokenEnum() == TokenEnum::eofTk) {
		throw CompilerException("Unecpected EOF\n");
	}
	//std::cout << list.front().getTokenEnum().toString() << "end_Node ";
	nul->node_name = "end";
	Token* token = new Token(list.front().getTokenEnum(), list.front().getTokenStr());
	nul->token = token;
	nul->loc = loc_cntr;
	list.erase(list.begin());
	loc_cntr++;
	return nul;
}

void Tree::defNode(Tree* node, std::vector<Token>& list) {
	node->loc = loc_cntr;
	Token* token = new Token(list.front().getTokenEnum(), list.front().getTokenStr());
	node->token = token;
	loc_cntr++;
	list.erase(list.begin());
}

Tree* Tree::tree_program(std::vector<Token>&list) 
{
	Tree* nul = new Tree;
	//std::cout << "\nTree_ program ";
	nul->node_name = "program";
	//std::cout  << list.front().getTokenEnum().toString() << "\n";
	nul->child1 = Tree::tree_vars(list);
	nul->child2 = Tree::tree_block(list);
	Tree::check_eof(list);
	return nul;
}

Tree* Tree::tree_block(std::vector<Token>& list)
{
	Tree* nul = new Tree;
	//std::cout << "\nTree_block ";
	nul->node_name = "block";
	//std::cout << list.front().getTokenEnum().toString() << "\n";
	if (list.front().getTokenEnum() == TokenEnum::voidKeyTk) {
		Tree::defNode(nul, list);
		//std::cout << list.front().getTokenEnum().toString() << "\n";
		nul->child1 = Tree::tree_vars(list);
		nul->child2 = Tree::tree_stats(list);
		if (list.front().getTokenEnum() == TokenEnum::returnKeyTk) {
			Tree::defNode(nul, list);
			return nul;
		}
		else {
			throw CompilerException("unexpected return token needed\n");
		}
	}
	else {
		throw CompilerException("unexpected void token needed \n");
	}
}

Tree* Tree::tree_vars(std::vector<Token>& list)
{
	Tree* nul = new Tree;
	//std::cout << "\nTree_vars ";
	nul->node_name = "vars";
	if (list.front().getTokenEnum() != TokenEnum::varKeyTk) {
		return NULL;
	}
	Tree::defNode(nul, list);
	if (list.front().getTokenEnum() != TokenEnum::id_tk) {
		throw CompilerException("error in Id  Var");
		return NULL;
	}
	nul->child1 = Tree::tree_end(list);
	if (list.front().getTokenEnum() != TokenEnum::colon_tk) {
		throw CompilerException("error in Colon Var");
		return NULL;
	}
	Tree::defNode(nul, list);
	if (list.front().getTokenEnum() != TokenEnum::int_tk) {
		throw CompilerException("error in Int Var");
		return NULL;
	}
	nul->child2 = Tree::tree_end(list);
	nul->child3 = Tree::tree_vars(list);
	return nul;
}

Tree* Tree::tree_expr(std::vector<Token>& list)
{
	Tree* nul = new Tree;
	//std::cout << "\nTree_expr ";
	nul->node_name = "expr";
	nul->child1=Tree::tree_A(list);
	if (list.front().getTokenEnum() == TokenEnum::plus_tk || list.front().getTokenEnum() == TokenEnum::minus_tk) {
		Tree::defNode(nul, list);
		nul->child2 = Tree::tree_expr(list);
		return nul;
	}
	else {
		return nul;
	}
}

Tree* Tree::tree_A(std::vector<Token>& list)
{
	Tree* nul = new Tree;
	//std::cout << "\nTree_A ";
	nul->node_name = "A";
	nul->child1 = Tree::tree_N(list);
	//std::cout << list.front().getTokenEnum().toString() << "\n";
	if (list.front().getTokenEnum() != TokenEnum::slash_tk) {
		return nul;
	}
	Tree::defNode(nul, list);
	nul->child2 = Tree::tree_A(list);
	return nul;
}

Tree* Tree::tree_N(std::vector<Token>& list) 
{
	Tree* nul = new Tree;
	//std::cout << "\nTree_N ";
	nul->node_name = "N";
	nul->child1 = Tree::tree_M(list);
	if (list.front().getTokenEnum() != TokenEnum::asterisk_tk) {
		return nul;
	}
	Tree::defNode(nul, list);
	nul->child2 = Tree::tree_N(list);
	return nul;
}

Tree* Tree::tree_M(std::vector<Token>& list)
{
	Tree* nul = new Tree;
	//std::cout << "\nTree_M ";
	nul->node_name = "M";
	if (list.front().getTokenEnum() == TokenEnum::pct_tk) {
		Tree::defNode(nul, list);
		nul->child1 = Tree::tree_M(list);
		return nul;
	}
	else {
		nul->child1 = Tree::tree_R(list);
		return nul;
	}
}

Tree* Tree::tree_R(std::vector<Token>& list) 
{
	Tree* nul = new Tree;
	//std::cout << "\nTree_R ";
	nul->node_name = "R";
	if (list.front().getTokenEnum() == TokenEnum::lpar_tk){
		Tree::defNode(nul, list);
		nul->child1 = Tree::tree_expr(list);
		if (list.front().getTokenEnum() != TokenEnum::rpar_tk) {
			throw CompilerException("Expected closing parenthesis.");
		}
		Tree::defNode(nul, list);
		return nul;
	}
	else if (list.front().getTokenEnum() == TokenEnum::id_tk){
		nul->child1 = Tree::tree_end(list);
		return nul;
	}
	else if (list.front().getTokenEnum() == TokenEnum::int_tk){
		nul->child1 = Tree::tree_end(list);
		return nul;
	}
	else{
		throw CompilerException("Unexpected token");
	}
}

Tree* Tree::tree_stats(std::vector<Token>& list)
{
	Tree* nul = new Tree;
	//std::cout << "\nTree_stats ";
	nul->node_name = "stats";
	nul->child1 = Tree::tree_stat(list);
	if (list.front().getTokenEnum() != TokenEnum::semicln_tk) {
		return NULL;
	}
	Tree::defNode(nul, list);
	nul->child2 = Tree::tree_mStat(list);
	return nul;
}

Tree* Tree::tree_mStat(std::vector<Token>& list)
{
	Tree* nul = new Tree;
	//std::cout << "\nTree_mStats ";
	nul->node_name = "mStat";
	//std::cout << list.front().getTokenEnum().toString() << "\n";
	switch(list.front().getTokenEnum()) {
		case TokenEnum::scanKeyTk:
		case TokenEnum::printKeyTk:
		case TokenEnum::voidKeyTk:
		case TokenEnum::condKeyTk:
		case TokenEnum::iterKeyTk:
		case TokenEnum::id_tk:
			nul->child1 = Tree::tree_stat(list);
			Tree::defNode(nul, list);
			nul->child2 = Tree::tree_mStat(list);
			return nul;
			break;
		default:
			return NULL;
			break;
	}
	return NULL;
}

Tree* Tree::tree_stat(std::vector<Token>& list)
{
	Tree* nul = new Tree;
	//std::cout << "\nTree_stat ";
	nul->node_name = "stat";
	switch (list.front().getTokenEnum()) {
		case TokenEnum::scanKeyTk:
			nul->child1 = Tree::tree_in(list);
			break;
		case TokenEnum::printKeyTk:
			nul->child1 = Tree::tree_out(list);
			break;
		case TokenEnum::voidKeyTk:
			nul->child1 = Tree::tree_block(list);
			break;
		case TokenEnum::condKeyTk:
			nul->child1 = Tree::tree_if(list);
			break;
		case TokenEnum::iterKeyTk:
			nul->child1 = Tree::tree_loop(list);
			break;
		case TokenEnum::id_tk:
			nul->child1 = Tree::tree_assign(list);
			break;
		default:
			throw CompilerException("Error from Tree stat");
			break;
	}
	return nul;
}

Tree* Tree::tree_in(std::vector<Token>& list) 
{
	Tree* nul = new Tree;
	//std::cout << "\nTree_in ";
	nul->node_name = "in";
	if (list.front().getTokenEnum() == TokenEnum::scanKeyTk) {
		Tree::defNode(nul, list);
		if (list.front().getTokenEnum() == TokenEnum::id_tk) {
			nul->child1 = Tree::tree_end(list);
			return nul;
		}
		else {
			throw CompilerException("error in IN");
		}
	}
	else {
		throw CompilerException("error in IN");
	}
}

Tree* Tree::tree_out(std::vector<Token> & list) 
{
	Tree* nul = new Tree;
	//std::cout << "\nTree_out ";
	nul->node_name = "out";
	if (list.front().getTokenEnum() == TokenEnum::printKeyTk) {
		Tree::defNode(nul, list);
		if (list.front().getTokenEnum() == TokenEnum::id_tk || list.front().getTokenEnum() == TokenEnum::int_tk || list.front().getTokenEnum() == TokenEnum::pct_tk) {
			nul->child1 = Tree::tree_expr(list);
			return nul;
		} 
		else {
			throw CompilerException("error in id  OUT");
		}
	}
	else {
		throw CompilerException("error in print OUT");
	}
}

Tree* Tree::tree_if(std::vector<Token>& list)
{
	Tree* nul = new Tree;
	//std::cout << "\nTree_if ";
	nul->node_name = "if";
	if (list.front().getTokenEnum() == TokenEnum::condKeyTk) {
		Tree::defNode(nul, list);
		if (list.front().getTokenEnum() == TokenEnum::lbkt_tk) {
			Tree::defNode(nul, list);
			nul->child1 = Tree::tree_expr(list);
			nul->child2 = Tree::tree_RO(list);
			nul->child3 = Tree::tree_expr(list);
			if (list.front().getTokenEnum() == TokenEnum::rbkt_tk) {
				Tree::defNode(nul, list);
				nul->child4 = Tree::tree_stat(list);
				return nul;
			}
			else {
				throw CompilerException("error in rbkt_tk IF");
			}
		}
		else {
			throw CompilerException("error in lbkt_tk IF");
		}
	}
	else {
		throw CompilerException("error in condKeyTk IF");
	}
}

Tree* Tree::tree_loop(std::vector<Token>& list)
{
	Tree* nul = new Tree;
	//std::cout << "\nTree_loop ";
	nul->node_name = "loop";
	if (list.front().getTokenEnum() == TokenEnum::iterKeyTk) {
		Tree::defNode(nul, list);
		if (list.front().getTokenEnum() == TokenEnum::lbkt_tk) {
			Tree::defNode(nul, list);
			nul->child1 = Tree::tree_expr(list);
			nul->child2 = Tree::tree_RO(list);
			nul->child3 = Tree::tree_expr(list);
			if (list.front().getTokenEnum() == TokenEnum::rbkt_tk) {
				Tree::defNode(nul, list);
				nul->child4 = Tree::tree_stat(list);
				return nul;
			}
			else {
				throw CompilerException("error in rbkt_tk loop");
			}
		}
		else {
			throw CompilerException("error in lbkt_tk loop");
		}
	}
	else {
		throw CompilerException("error in iterKeyTk loop");
	}
}

Tree* Tree::tree_assign(std::vector<Token>& list)
{
	Tree* nul = new Tree;
	//std::cout << "\nTree_assign ";
	nul->node_name = "assign";
	if (list.front().getTokenEnum() == TokenEnum::id_tk) {
		nul->child1 = Tree::tree_end(list);
		if (list.front().getTokenEnum() == TokenEnum::eq_tk) {
			Tree::defNode(nul, list);
			nul->child2 = Tree::tree_expr(list);
			return nul;
		}
		else {
			throw CompilerException("error in IF");
		}
	}
	else {
		throw CompilerException("error in IF");
	}
}

Tree* Tree::tree_RO(std::vector<Token>& list)
{
	Tree* nul = new Tree;
	//std::cout << "\nTree_RO ";
	nul->node_name = "RO";
	switch (list.front().getTokenEnum()) {
	case TokenEnum::lt_tk:
		nul->child1 = Tree::tree_end(list);
		if (list.front().getTokenEnum() == TokenEnum::lgt_tk) {
			nul->child2 = Tree::tree_end(list);
		}
		return nul;
		break;
	case TokenEnum::eq_tk:
		nul->child1 = Tree::tree_end(list);
		if (list.front().getTokenEnum() == TokenEnum::lgt_tk || list.front().getTokenEnum() == TokenEnum::lt_tk) {
			nul->child2 = Tree::tree_end(list);
		}
		return nul;
		break;
	case TokenEnum::lgt_tk:
		nul->child1 = Tree::tree_end(list);
		return nul;
		break;
	default:
		throw CompilerException("Error from Tree RO");
		break;
	}
	return nul;

}

void Tree::check_eof(std::vector<Token> list) {
	if (list.front().getTokenEnum() != TokenEnum::eofTk)
		throw CompilerException("Unexpected token after end");
}