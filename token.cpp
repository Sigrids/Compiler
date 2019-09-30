#include "exceptions.h"
#include "token.h"

Token::Token(TokenEnum m, std::string i) {
	tokenenum = m;
	tokenstr = i;
}

Token::Token(std::string str)
{
	tokenenum = TokenEnum::getTokenEnum(str);
	tokenstr = str;
}

TokenEnum Token::getTokenEnum()
{
	return tokenenum;
}

std::string Token::getTokenStr()
{
	return tokenstr;
}