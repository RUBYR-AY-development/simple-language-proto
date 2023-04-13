/*
* Creates new tokens based on syntax.
* Example:
* var <const> a = 1
*     ^^^^^^^
* It would be converted to a variable tag token
*/

#include <iostream>
#include <vector>
#include <format>
#include "token.h"
#include "syntax_tok.h"
#include "syntax_tokens.h"
#include "../../Util/smallfunc.h"

// small functions instead of repeating conditions
inline bool WITHIN_ANGLE_BRACKETS(int& token_pos, std::vector<TOKEN>& TOKENS)
{
    // < >
    if ((token_pos > 0 && token_pos < TOKENS.size()) &&
        TOKENS[token_pos - 1].type == "LESS_THAN" &&
        TOKENS[token_pos + 1].type == "GREATER_THAN")
        return true;
    return false;
}


void syntax_tok::handle(std::vector<TOKEN>& TOKENS)
{
    // will call 'new_line' for each line
    int line = 1; // only for display_err

    for (int token_pos = 0; token_pos < TOKENS.size(); token_pos++)
    {
        TOKEN token = TOKENS[token_pos];
        if (token.type == "EOF")
            break;
        if (token.type == "EOL")
            line++;

        if (token.type == "IDENTIFIER")
        {
            if (WITHIN_ANGLE_BRACKETS(token_pos, TOKENS))
            {
                // variable token
                // NOTE: empty angle bracket detection is in 'err_tokens.cpp'
                if (TOKENS[token_pos - 2].value == "var" &&
                    TOKENS[token_pos - 2].type == "KEYWORD")
                {
                    if (VAR_TAGS.count(token.value))
                    {
                        // a valid variable tag
                        for (int i = 0; i < 3; i++)
                            TOKENS.erase(TOKENS.begin() + token_pos - 1);
                        TOKENS.insert(TOKENS.begin() + token_pos - 1, TOKEN{ "VAR_TAG",token.value });
                    }
                    else
                        display_err(line, std::format("Invalid variable tag '{0}'", token.value).c_str());
                } // end of variable token

            } // end of WITHIN_ANGLE_BRACKETS

        } // end of IDENTIFIER
    }
}