#pragma once
#include <iostream>
#include <vector>
#include "../../create_tree.h"

namespace var_decl {
	void handle(int& line, std::vector<TOKEN>& TOKENS, node* RAW_TREE);
}