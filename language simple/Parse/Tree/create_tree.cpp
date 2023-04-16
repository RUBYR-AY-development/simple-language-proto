#include <iostream>
#include <vector>
#include "create_tree.h"
#include "../../Util/smallfunc.h"
#include "err_handle_tree.h"

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
		{
			// remove some tokens first
			int at = 0;
			for (TOKEN x : TOKENS)
			{
				if (x.type == "EOL" ||
					x.type == "EOF" ||
					x.type == "KEYWORD" &&
						x.value == "var")
				{
					TOKENS.erase(TOKENS.begin() + at);
					at++;
				}
			} // END OF REMOVING

			RAW_TREE->data.type = "VAR_DECLARE";
			bool PASSED_EQ = false;
			int COUNT = 0; // error detection
			for (TOKEN x : TOKENS)
			{
				if (x.type == "QUOTATION_DOUBLE" || x.type == "QUOTATION_SINGLE")
					continue;
				if (x.type == "KEYWORD")
					display_err(line, "Invalid variable declaration expression");

				if (x.type == "EQUAL") {
					COUNT = 0;
					PASSED_EQ = true;
					continue;
				}
				if (x.type == "VAR_TAG") {
					RAW_TREE->add_child(TREE_TOK{ "VAR_TAG",{x.value} });
					continue;
				}
				if (x.type == "IDENTIFIER") {
					COUNT++;
					if (!PASSED_EQ)
						RAW_TREE->add_child(TREE_TOK{ "VAR_NAME",{x.value} });
					continue;
				}

				if (COUNT > 1)
					// ez error catcher
					display_err(line, "Invalid variable declaration expression");
				COUNT++;
				RAW_TREE->add_child(TREE_TOK{ "VALUE",{x.value,x.type} });
			}
		}
	}

	print_tree(RAW_TREE);
	//err_handle_tree::handle(line, RAW_TREE);

	return RAW_TREE;
}