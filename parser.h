#pragma once
#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>
#include <cstdio>
#include <memory>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include "exceptions.h"
#include "tokenEnum.h"
#include "tree.h"
#include "token.h"
#include "scanner.h"

Tree* parser(int, char**);

#endif // PARSER_H