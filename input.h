#pragma once
#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <string>
#include "token.h"

FILE* getfp(int, char**);
std::string next(FILE*);
void closefp(FILE*);

#endif // INPUT_H