/*
* Creates new tokens based on syntax.
* Example:
* var <const> a = 1
*     ^^^^^^^
* It would be converted to a variable tag token
*/

#include <iostream>
#include <vector>
#include "token.h"
#include "syntax_tok.h"

void syntax_tok::handle(std::vector<TOKEN>& TOKENS)
{
    // will call 'new_line' for each line
    for (int token_pos = 0; token_pos < TOKENS.size(); token_pos++)
    {
        TOKEN token = TOKENS[token_pos];
        if (token.type == "EOF")
            break;

        // variable token
        if (token.type == "IDENTIFIER" &&
            TOKENS[token_pos - 1].type == "LESS_THAN" &&
            TOKENS[token_pos + 1].type == "GREATER_THAN" &&
            (TOKENS[token_pos - 2].value == "var" &&
                TOKENS[token_pos - 2].type == "KEYWORD"))
        {
            // if then
            if (token.value == "const")
            {
                for (int i = 0; i < 3; i++)
                    TOKENS.erase(TOKENS.begin() + token_pos - 1);
                TOKENS.insert(TOKENS.begin() + token_pos - 1, TOKEN{ "VAR_TAG",token.value });
            }
        }
    }
}