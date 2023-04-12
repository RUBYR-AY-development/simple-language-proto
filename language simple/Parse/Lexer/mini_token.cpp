/*
* Contains 'Lexer' class function 'ADD_TOKEN'
* This is for the tokens that are one byte (char)
*/

#include <iostream>
#include "token.h"
#include "tokenizer.h"

void LEXER::ADD_TOKEN(TOKEN_TYPES TYPE)
{
	switch (TYPE)
	{
		case TOKEN_TYPES::EOL:
		{
			this->TOKENS.push_back(TOKEN{ "EOL","EOL" });
			break;
		}
		case TOKEN_TYPES::_EOF_:
		{
			this->TOKENS.push_back(TOKEN{ "EOF","EOF" });
			break;
		}
		case TOKEN_TYPES::LEFT_PAREN:
		{
			if (!this->ignore_all_tokens)
			{
				if (!this->in_string)
				{
					this->ADD_CUR_TOK();
					this->TOKENS.push_back(TOKEN{ "LEFT_PAREN","(" });
				}
				else
					this->CUR_TOK += "(";
			}
			break;
		}
		case TOKEN_TYPES::RIGHT_PAREN:
		{
			if (!this->ignore_all_tokens)
			{
				if (!this->in_string)
				{
					this->ADD_CUR_TOK();
					this->TOKENS.push_back(TOKEN{ "RIGHT_PAREN",")" });
				}
				else
					this->CUR_TOK += ")";
			}
			break;
		}
		case TOKEN_TYPES::QUOTATION_DOUBLE:
		{
			if (!this->ignore_all_tokens)
			{
				if (this->in_string)
				{
					// string completed
					this->TOKENS.push_back(TOKEN{ "STRING_LITERAL",this->CUR_TOK });
					this->CUR_TOK = "";
				}
				this->in_string = !this->in_string;
				this->TOKENS.push_back(TOKEN{ "QUOTATION_DOUBLE","\"" });
			}
			break;
		}
		case TOKEN_TYPES::QUOTATION_SINGLE:
		{
			if (!this->ignore_all_tokens)
			{
				this->TOKENS.push_back(TOKEN{ "QUOTATION_SINGLE","'" });
			}
			break;
		}
		case TOKEN_TYPES::DOT:
		{
			if (!this->ignore_all_tokens)
			{
				if (!this->in_string)
				{
					this->ADD_CUR_TOK();
					this->TOKENS.push_back(TOKEN{ "DOT","." });
				}
				else
					this->CUR_TOK += ".";
			}
			break;
		}
		case TOKEN_TYPES::SEMICOLON:
		{
			if (!this->ignore_all_tokens)
			{
				if (!this->in_string)
				{
					this->TOKENS.push_back(TOKEN{ "SEMICOLON",";" });
				}
				else
					this->CUR_TOK += ";";
			}
			break;
		}
		case TOKEN_TYPES::COLON:
		{
			if (!this->ignore_all_tokens)
			{
				if (!this->in_string)
				{
					this->ADD_CUR_TOK();
					this->TOKENS.push_back(TOKEN{ "COLON",":" });
				}
				else
					this->CUR_TOK += ":";
			}
			break;
		}
		case TOKEN_TYPES::PLUS:
		{
			if (!this->ignore_all_tokens)
			{
				if (!this->in_string)
				{
					if (this->TOKENS.back() == TOKEN{ "PLUS","+" })
					{
						this->TOKENS.pop_back();
						this->TOKENS.push_back(TOKEN{ "INCREMENT_ONE","++" });
					}
					else
					{
						this->ADD_CUR_TOK();
						this->TOKENS.push_back(TOKEN{ "PLUS","+" });
					}
				}
				else
					this->CUR_TOK += "+";
			}
			break;
		}
		case TOKEN_TYPES::MINUS:
		{
			if (!this->ignore_all_tokens)
			{
				if (!this->in_string)
				{
					if (this->TOKENS.back() == TOKEN{ "MINUS","-" })
					{
						this->TOKENS.pop_back();
						this->TOKENS.push_back(TOKEN{ "DECREMENT_ONE","--" });
					}
					else
					{
						this->ADD_CUR_TOK();
						this->TOKENS.push_back(TOKEN{ "MINUS","-" });
					}
				}
				else
					this->CUR_TOK += "-";
			}
			break;
		}
		case TOKEN_TYPES::STAR:
		{
			if (!this->ignore_all_tokens)
			{
				if (!this->in_string)
				{
					this->ADD_CUR_TOK();
					this->TOKENS.push_back(TOKEN{ "STAR","*" });
				}
				else
					this->CUR_TOK += "*";
			}
			break;
		}
		case TOKEN_TYPES::FRONT_SLASH:
		{
			if (!this->in_string)
			{
				// PREVIOUS TOKEN CHECK
				if (this->TOKENS.back() == TOKEN{ "FRONT_SLASH","/" })
				{
					// check if its a comment
					this->ignore_all_tokens = true;
	
					// get rid of the previous frontslash
					this->TOKENS.pop_back();
				}
				else
				{
					this->ADD_CUR_TOK();
					this->TOKENS.push_back(TOKEN{ "FRONT_SLASH","/" });
				}
			}
			else
				this->CUR_TOK += "/";
			break;
		}
		case TOKEN_TYPES::GREATER_THAN:
		{
			if (!this->ignore_all_tokens)
			{
				if (!this->in_string)
				{
					this->ADD_CUR_TOK();
					this->TOKENS.push_back(TOKEN{ "GREATER_THAN",">" });
				}
				else
					this->CUR_TOK += ">";
			}
			break;
		}
		case TOKEN_TYPES::LESS_THAN:
		{
			if (!this->ignore_all_tokens)
			{
				if (!this->in_string)
				{
					this->ADD_CUR_TOK();
					this->TOKENS.push_back(TOKEN{ "LESS_THAN","<" });
				}
				else
					this->CUR_TOK += "<";
			}
			break;
		}
		case TOKEN_TYPES::EQUAL:
		{
			if (!this->ignore_all_tokens)
			{
				if (!this->in_string)
				{
					auto bacc = this->TOKENS.back();
					if (bacc == TOKEN{ "EQUAL","=" })
					{
						this->TOKENS.pop_back();
						this->TOKENS.push_back(TOKEN{ "EQUAL_EQUAL","==" });
					}
					// greater or eq
					else if (bacc == TOKEN{ "GREATER_THAN",">" })
					{
						this->TOKENS.pop_back();
						this->TOKENS.push_back(TOKEN{ "GREATER_OR_EQ",">=" });
					}
					// less or eq
					else if (bacc == TOKEN{ "LESS_THAN","<" })
					{
						this->TOKENS.pop_back();
						this->TOKENS.push_back(TOKEN{ "LESS_OR_EQ","<=" });
					}
					// regular equal
					else
					{
						this->ADD_CUR_TOK();
						this->TOKENS.push_back(TOKEN{ "EQUAL","=" });
					}
				}
				else
					this->CUR_TOK += "=";
			}
			break;
		}
		case TOKEN_TYPES::COMMA:
		{
			if (!this->ignore_all_tokens)
			{
				if (!this->in_string)
				{
					this->ADD_CUR_TOK();
					this->TOKENS.push_back(TOKEN{ "COMMA","," });
				}
				else
					this->CUR_TOK += ",";
			}
			break;
		}
		case TOKEN_TYPES::LEFT_CURLY_BRACE:
		{
			if (!this->ignore_all_tokens)
			{
				if (!this->in_string)
				{
					this->ADD_CUR_TOK();
					this->TOKENS.push_back(TOKEN{ "LEFT_CURLY_BRACE","{" });
				}
				else
					this->CUR_TOK += "{";
			}
			break;
		}
		case TOKEN_TYPES::RIGHT_CURLY_BRACE:
		{
			if (!this->ignore_all_tokens)
			{
				if (!this->in_string)
				{
					this->ADD_CUR_TOK();
					this->TOKENS.push_back(TOKEN{ "RIGHT_CURLY_BRACE","}" });
				}
				else
					this->CUR_TOK += "}";
			}
			break;
		}
	}
}