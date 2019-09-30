#pragma once
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>
#include <iostream>
#include <cstdio>
#include <sstream>

class CompilerException : public std::exception {
public:
	CompilerException() :
		exceptionMessage("Compiler Error:") {}
	explicit CompilerException(std::string message) :
		exceptionMessage(std::move(message)) {}
	const char* what() const throw() {
		std::cout << "Compiler Error:" << exceptionMessage << std::endl;

		std::stringstream s;
		s << "Compiler Error: " << exceptionMessage << std::endl;

		std::string whatString = s.str();
		const char* c = whatString.c_str();
		return c;
	}
private:
	std::string exceptionMessage;
};
#endif