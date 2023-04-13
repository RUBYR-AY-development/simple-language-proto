/*
* defines 'symbols.h' data
*/

#include <iostream>
#include <set>
#include "symbols.h"

std::set<std::string> KEYWORD_SYMBOLS =
{
	"var",
	"if",
	"end",
	"else",
	"begin"
};
std::set<std::string> BUILTIN_FUNCS =
{
	"display"
};