/*
* Seperates every token into expressions
*/

#include <iostream>
#include <vector>
#include "tree_main.h"
#include "../Lexer/token.h"
#include "create_tree.h"

node* new_line(int& line, std::vector<TOKEN>& TOKENS)
{
	// unfinished lol
	node* TREE = tree_make::create(line, TOKENS);
	return TREE;
}

void tree_main::handle(std::vector<TOKEN>& TOKENS)
{
	std::vector<TOKEN> cur_toks;
	std::vector<node*> trees;
	int line = 1;

	for (TOKEN token : TOKENS)
	{
		if (token.type == "EOF")
			break;
		if (token.type == "EOL" || token.type == "SEMICOLON")
		{
			trees.push_back(new_line(line, cur_toks));
			cur_toks.clear();
			line++;
		}
		else
			cur_toks.push_back(token);
	}
}