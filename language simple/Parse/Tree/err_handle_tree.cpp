#include "err_handle_tree.h"
#include "../../Util/smallfunc.h"

void err_handle_tree::handle(int& line,node* TREE)
{
	// looks for tokens
	if (TREE->data.type == "VAR_DECLARE")
	{
		int amnt_there = 0; // amount of valid tokens present
		bool var_tag_enabled = false;
		for (node* NODE : TREE->children)
		{
			if (NODE->data.type == "VAR_TAG") {
				var_tag_enabled = true;
				amnt_there++;
				continue;
			}
			if (NODE->data.type == "VALUE") {
				amnt_there++;
				continue;
			}
			if (NODE->data.type == "VAR_NAME")
				amnt_there++;
		}
		if (!var_tag_enabled)
			if (amnt_there < 2)
				display_err(line, "Invalid variable declaration expression");
		else
			if (amnt_there < 3)
				display_err(line, "Invalid variable declaration expression");
		return;
	}
}