
#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include "tokenEnum.h"

class Token
{
public:
	Token(TokenEnum, std::string);
	Token(std::string);
	TokenEnum getTokenEnum();
	std::string getTokenStr();
private:
	TokenEnum tokenenum = TokenEnum::getTokenEnum("");
	std::string tokenstr;
};

#endif /* TOKEN_H */