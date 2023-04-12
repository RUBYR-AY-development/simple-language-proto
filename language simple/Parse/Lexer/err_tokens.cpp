/*
* Small token error checks
*/

#include <iostream>
#include <vector>
#include <format>
#include "tokenizer.h"
#include "err_tokens.h"
#include "../../Util/smallfunc.h"

inline void display_err(int line, const char* MESSAGE)
{
    std::cout << "Line " << line << " Syntax error; Msg: ";
    std::cerr << MESSAGE;
    std::exit(1);
}

void new_line(int& line, const std::vector<TOKEN>& TOKENS)
{
    // for now, this will be the detection
    int quote_amnt = 0;
    int paren_amnt = 0;
    int curly_amnt = 0;

    TOKEN* last_token = nullptr;

    // reading those tokens
    for (TOKEN token : TOKENS)
    {
        if (token.type == "QUOTATION_DOUBLE" || token.type == "QUOTATION_SINGLE")
            quote_amnt++;
        if (token.type == "LEFT_PAREN" || token.type == "RIGHT_PAREN")
            paren_amnt++;
        if (token.type == "LEFT_CURLY_BRACE" || token.type == "RIGHT_CURLY_BRACE")
            curly_amnt++;

        if (last_token != nullptr)
            if (last_token->type == token.type)
                display_err(line, std::format("Invalid expression; Double type {0}",token.type).c_str());
        last_token = &token;
    }

    if (!is_even(quote_amnt))
        display_err(line, "Malformed string");
    if (!is_even(paren_amnt))
        display_err(line, "Missing parenthesis");
    if (!is_even(curly_amnt))
        display_err(line, "Missing curly brace");

    delete last_token;
}

void err_tokens::handle(std::vector<TOKEN>& TOKENS)
{
    std::vector<TOKEN> cur_toks;
    int line = 1;

    // will call 'new_line' for each line
    for (TOKEN token : TOKENS)
    {
        if (token.type == "EOF")
            break;
        if (token.type == "EOL")
        {
            new_line(line,cur_toks);
            cur_toks.clear();
            line++;
        }
        else
            cur_toks.push_back(token);
    }
}