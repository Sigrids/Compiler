#include <string>
#include <iostream>
#include <cstdio>
#include <memory>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include "exceptions.h"
#include "input.h"
#include "token.h"

FILE* getfp(int ar, char** argv) {
	FILE* fi;
	if (ar == 2) {
		std::string ext = ".sp19";
		std::string base = argv[1];
		base.append(ext);
		fi = fopen(base.c_str(), "r");
		if (!fi) {
			std::cout << "parser Error: " << base << " failed to open.\n";
		}
	}
	else if (ar == 1) {
		fi = stdin;
	}
	else {
		std::string execp = "To many args";
		throw CompilerException(execp);
	}
	return fi;
}

std::string next(FILE* fp) {
	char buffer[240];
	std::string word;

	if (fscanf(fp, "%s", buffer) < 1) {
		return "";
	}
	else {
		word = buffer;
		return word;
	}
}

void closefp(FILE* fp) {
	if (fclose(fp) != 0){
		throw CompilerException("Error closing file");
	}
}