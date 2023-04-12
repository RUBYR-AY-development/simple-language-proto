/*
* Main part of the lexer
* code for 'LEXER' class functions
*/

#include <iostream>
#include <vector>
#include "tokenizer.h"
#include "symbols.h"
#include "token.h"
#include "err_tokens.h"

constexpr bool PRINT_TOKENS = true;
constexpr bool DEBUG_MODE = false; // error checking

void LEXER::ADD_CUR_TOK()
{
	if (this->CUR_TOK != "" && !this->ignore_all_tokens)
	{
		if (KEYWORD_SYMBOLS.count(this->CUR_TOK))
		{
			this->TOKENS.push_back(TOKEN{ "KEYWORD",this->CUR_TOK });
			this->CUR_TOK = "";
			return;
		}
		if (BUILTIN_FUNCS.count(this->CUR_TOK))
		{
			this->TOKENS.push_back(TOKEN{ "FUNCTION",this->CUR_TOK });
			this->CUR_TOK = "";
			return;
		}


		// if everything else is false
		this->TOKENS.push_back(TOKEN{ "IDENTIFIER",this->CUR_TOK });
		this->CUR_TOK = "";
		return;
	}
}

LEXER::LEXER(std::vector<std::string>& LINES)
{
	this->LINES = LINES;
	this->TXT = this->LINES[this->cycle];

	// CYCLE FOR EACH LINE
	while (this->cycle < LINES.size())
	{

		// CYCLE FOR EACH CHARACTER
		while (this->CURRENT() != '\0')
		{
			switch (this->CURRENT())
			{
				case '(': {this->ADD_TOKEN(TOKEN_TYPES::LEFT_PAREN); break; }
				case ')': {this->ADD_TOKEN(TOKEN_TYPES::RIGHT_PAREN); break; }
				case '"': {this->ADD_TOKEN(TOKEN_TYPES::QUOTATION_DOUBLE); break; }
				case '\'': {this->ADD_TOKEN(TOKEN_TYPES::QUOTATION_SINGLE); break; }
				case '.': {this->ADD_TOKEN(TOKEN_TYPES::DOT); break; }
				case ';': {this->ADD_TOKEN(TOKEN_TYPES::SEMICOLON); break; }
				case ':': {this->ADD_TOKEN(TOKEN_TYPES::COLON); break; }
				case '+': {this->ADD_TOKEN(TOKEN_TYPES::PLUS); break; }
				case '-': {this->ADD_TOKEN(TOKEN_TYPES::MINUS); break; }
				case '*': {this->ADD_TOKEN(TOKEN_TYPES::STAR); break; }
				case '/': {this->ADD_TOKEN(TOKEN_TYPES::FRONT_SLASH); break; }
				case '>': {this->ADD_TOKEN(TOKEN_TYPES::GREATER_THAN); break; }
				case '<': {this->ADD_TOKEN(TOKEN_TYPES::LESS_THAN); break; }
				case '=': {this->ADD_TOKEN(TOKEN_TYPES::EQUAL); break; }
				case ',': {this->ADD_TOKEN(TOKEN_TYPES::COMMA); break; }
				case '{': {this->ADD_TOKEN(TOKEN_TYPES::LEFT_CURLY_BRACE); break; }
				case '}': {this->ADD_TOKEN(TOKEN_TYPES::RIGHT_CURLY_BRACE); break; }

				case ' ':
				{
					if (this->in_string)
						this->CUR_TOK += this->CURRENT();
					else
						this->ADD_CUR_TOK();
					break;
				}
				default:
				{
					this->CUR_TOK += this->CURRENT();
					break;
				}
			}

			this->ADVANCE();
		}

		this->ADVANCE_NEXT_TXT();
		this->ADD_TOKEN(TOKEN_TYPES::EOL);
	}
	this->ADD_TOKEN(TOKEN_TYPES::_EOF_);

	if (!DEBUG_MODE)
		err_tokens::handle(this->TOKENS);
	if (PRINT_TOKENS)
		for (auto x : this->TOKENS)
			std::cout << "[" << x.type << "] " << x.value << std::endl;
}