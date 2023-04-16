#include <iostream>
#include <vector>
#include "create_tree.h"
#include "../../Util/smallfunc.h"
#include "err_handle_tree.h"
#include "tree_types/var/var_decl.h"

void print_tree(node* TREE)
{
	std::cout << TREE->data.type << ' ' << TREE->data.init.raw_value << '\n';
	for (auto x : TREE->children)
		print_tree(x);
}


node* tree_make::create(int& line, std::vector<TOKEN>& TOKENS)
{
	// make tree
	node* RAW_TREE = new node(TREE_TOK{ "ROOT" });
	TOKEN front = TOKENS.front();
	// keyword branch
	if (front.type == "KEYWORD")
	{
		if (front.value == "var")
			var_decl::handle(line, TOKENS, RAW_TREE);
	}

	print_tree(RAW_TREE);
	err_handle_tree::handle(line, RAW_TREE);

	return RAW_TREE;
}