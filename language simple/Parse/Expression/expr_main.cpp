/*
* Seperates every token into expressions
*/

#include <iostream>
#include <vector>
#include "expr_main.h"
#include "../Lexer/token.h"
#include "expression.h"

std::vector<EXPRESSION> new_line(int& line, std::vector<TOKEN>& TOKENS)
{
	std::vector<EXPRESSION> expressions;

	return expressions;
}

void expr_main::handle(std::vector<TOKEN>& TOKENS)
{
	std::vector<TOKEN> cur_toks;
	std::vector<std::vector<EXPRESSION>> expressions;
	int line = 1;

	for (TOKEN token : TOKENS)
	{
		if (token.type == "EOF")
			break;
		if (token.type == "EOL")
		{
			expressions.push_back(new_line(line, cur_toks));
			cur_toks.clear();
			line++;
		}
		else
			cur_toks.push_back(token);
	}
}