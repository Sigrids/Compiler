#include <string>
#include "tokenEnum.h"
#include "exceptions.h"

std::string TokenEnum::getTokenEnumString(TokenEnum type)
{
	switch (type)
	{
	case voidKeyTk:
		return "voidKeyTk";
		break;
	case intKeyTk:
		return "intKeyTk";
		break;
	case returnKeyTk:
		return "returnKeyTk";
		break;
	case printKeyTk:
		return "printKeyTk";
		break;
	case scanKeyTk:
		return "scanKeyTk";
		break;
	case programKeyTk:
		return "programKeyTk";
		break;
	case iterKeyTk:
		return "iterKeyTk";
		break;
	case varKeyTk:
		return "varKeyTk";
		break;
	case condKeyTk:
		return "condKeyTk";
		break;
	case thenKeyTk:
		return "thenKeyTk";
		break;
	case letKeyTk:
		return "letKeyTk";
		break;
	case eq_tk:
		return "eq_tk";
		break;
	case lt_tk:
		return "lt_tk";
		break;
	case lgt_tk:
		return "lgt_tk";
		break;
	case colon_tk:
		return "colon_tk";
		break;
	case plus_tk:
		return "plus_tk";
		break;
	case minus_tk:
		return "minus_tk";
		break;
	case asterisk_tk:
		return "asterisk_tk";
		break;
	case slash_tk:
		return "slash_tk";
		break;
	case pct_tk:
		return "pct_tk";
		break;
	case dot_tk:
		return "dot_tk";
		break;
	case lpar_tk:
		return "lpar_tk";
		break;
	case rpar_tk:
		return "rpar_tk";
		break;
	case comma_tk:
		return "comma_tk";
		break;
	case lbrace_tk:
		return "lbrace_tk";
		break;
	case rbrace_tk:
		return "rbrace_tk";
		break;
	case semicln_tk:
		return "semicln_tk";
		break;
	case lbkt_tk:
		return "lbkt_tk";
		break;
	case rbkt_tk:
		return "rbkt_tk";
		break;
	case id_tk:
		return "id_tk";
		break;
	case int_tk:
		return "int_tk";
		break;
	case commentTk:
		return "commentTk";
		break;
	case eofTk:
		return "eofTk";
		break;
	default:
		throw CompilerException("enumtoStr():Unrecognized token");
		break;
	}
}

TokenEnum TokenEnum::getTokenEnumFromString(std::string str)
{
	if (str == "voidKeyTk") {
		return TokenEnum::voidKeyTk;
	}
	else if (str == "intKeyTk") {
		return TokenEnum::intKeyTk;
	}
	else if (str == "returnKeyTk") {
		return TokenEnum::returnKeyTk;
	}
	else if (str == "printKeyTk") {
		return TokenEnum::printKeyTk;
	}
	else if (str == "scanKeyTk") {
		return TokenEnum::scanKeyTk;
	}
	else if (str == "programKeyTk") {
		return TokenEnum::programKeyTk;
	}
	else if (str == "iterKeyTk") {
		return TokenEnum::iterKeyTk;
	}
	else if (str == "varKeyTk") {
		return TokenEnum::varKeyTk;
	}
	else if (str == "condKeyTk") {
		return TokenEnum::condKeyTk;
	}
	else if (str == "thenKeyTk") {
		return TokenEnum::thenKeyTk;
	}
	else if (str == "letKeyTk") {
		return TokenEnum::letKeyTk;
	}
	else if (str == "eq_tk") {
		return TokenEnum::eq_tk;
	}
	else if (str == "lt_tk") {
		return TokenEnum::lt_tk;
	}
	else if (str == "lgt_tk") {
		return TokenEnum::lgt_tk;
	}
	else if (str == "colon_tk") {
		return TokenEnum::colon_tk;
	}
	else if (str == "plus_tk") {
		return TokenEnum::plus_tk;
	}
	else if (str == "minus_tk") {
		return TokenEnum::minus_tk;
	}
	else if (str == "asterisk_tk") {
		return TokenEnum::asterisk_tk;
	}
	else if (str == "slash_tk") {
		return TokenEnum::slash_tk;
	}
	else if (str == "pct_tk") {
		return TokenEnum::pct_tk;
	}
	else if (str == "dot_tk") {
		return TokenEnum::dot_tk;
	}
	else if (str == "lpar_tk") {
		return TokenEnum::lpar_tk;
	}
	else if (str == "rpar_tk") {
		return TokenEnum::rpar_tk;
	}
	else if (str == "comma_tk") {
		return TokenEnum::comma_tk;
	}
	else if (str == "lbrace_tk") {
		return TokenEnum::lbrace_tk;
	}
	else if (str == "rbrace_tk") {
		return TokenEnum::rbrace_tk;
	}
	else if (str == "semicln_tk") {
		return TokenEnum::semicln_tk;
	}
	else if (str == "lbkt_tk") {
		return TokenEnum::lbkt_tk;
	}
	else if (str == "lbkt_tk") {
		return TokenEnum::lbkt_tk;
	}
	else if (str == "id_tk") {
		return TokenEnum::id_tk;
	}
	else if (str == "int_tk") {
		return TokenEnum::int_tk;
	}
	else if (str == "commentTk") {
		return TokenEnum::commentTk;
	}
	else if (str == "eofTk") {
		return TokenEnum::eofTk;
	}

	throw CompilerException("Invalid token type ");
}

TokenEnum TokenEnum::getTokenEnum(std::string str)
{
	if (!check_alpha(str)) {
		throw CompilerException("Token:Not valid string");
	}
	if (str == "void") {
		return TokenEnum::voidKeyTk;
	}
	else if (str == "int") {
		return TokenEnum::intKeyTk;
	}
	else if (str == "return") {
		return TokenEnum::returnKeyTk;
	}
	else if (str == "print") {
		return TokenEnum::printKeyTk;
	}
	else if (str == "scan") {
		return TokenEnum::scanKeyTk;
	}
	else if (str == "program") {
		return TokenEnum::programKeyTk;
	}
	else if (str == "iter") {
		return TokenEnum::iterKeyTk;
	}
	else if (str == "var") {
		return TokenEnum::varKeyTk;
	}
	else if (str == "cond") {
		return TokenEnum::condKeyTk;
	}
	else if (str == "then") {
		return TokenEnum::thenKeyTk;
	}
	else if (str == "let") {
		return TokenEnum::letKeyTk;
	}
	else if (str == "=") {
		return TokenEnum::eq_tk;
	}
	else if (str == "<") {
		return TokenEnum::lt_tk;
	}
	else if (str == ">") {
		return TokenEnum::lgt_tk;
	}
	else if (str == ":") {
		return TokenEnum::colon_tk;
	}
	else if (str == "+") {
		return TokenEnum::plus_tk;
	}
	else if (str == "-") {
		return TokenEnum::minus_tk;
	}
	else if (str == "*") {
		return TokenEnum::asterisk_tk;
	}
	else if (str == "/") {
		return TokenEnum::slash_tk;
	}
	else if (str == "%") {
		return TokenEnum::pct_tk;
	}
	else if (str == ".") {
		return TokenEnum::dot_tk;
	}
	else if (str == "(") {
		return TokenEnum::lpar_tk;
	}
	else if (str == ")") {
		return TokenEnum::rpar_tk;
	}
	else if (str == ",") {
		return TokenEnum::comma_tk;
	}
	else if (str == "{") {
		return TokenEnum::lbrace_tk;
	}
	else if (str == "}") {
		return TokenEnum::rbrace_tk;
	}
	else if (str == ";") {
		return TokenEnum::semicln_tk;
	}
	else if (str == "[") {
		return TokenEnum::lbkt_tk;
	}
	else if (str == "]") {
		return TokenEnum::rbkt_tk;
	}
	else if (is_id(str)) {
		return TokenEnum::id_tk;
	}
	else if (is_int(str)) {
		return TokenEnum::int_tk;
	}
	else if (str == "") {
		return TokenEnum::eofTk;
	}

	// if the above conditional hasnt returned a token, the string is unknown and therefore erroneous.
	throw CompilerException("Unknown token");
}

std::string TokenEnum::toString()
{
	return TokenEnum::getTokenEnumString(t_);
}

static bool check_alpha(std::string str) {
	char c;
	for (int i = 0; i < str.length(); i++) {
		c = str[i];
		if (c < 32 || c > 125) { // chars outside of this range are not allowed
			return false;
		}
		switch (c) { //check for unallowed characters
		case 33:
		case 34:
		case 35:
		case 36:
		case 38:
		case 39:
		case 63:
		case 64:
		case 92:
		case 94:
		case 95:
		case 96:
		case 124:
			return false;
			break;
		default:
			break;
		}
	}
	return true;
}
static bool is_id(std::string str) {
	if (str.length() < 1 || str.length() > 8) {
		return false;
	}

	if (isalpha(str[0]) != 0) {
		return true;
	}
	else {
		return false;
	}
	return true;
}
static bool is_int(std::string str) {
	if (str.length() < 1 || str.length() > 8) {
		return false;
	}
	char c;

	for (int i = 0; i < str.length(); i++) {
		c = str[i];
		if (!(c <= '9' && c >= '0')) {
			return false;
		}
	}
	return true;
}
