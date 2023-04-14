#pragma once
#include <iostream>
#include <vector>
#include "token.h"

class LEXER
{
	public:
		LEXER(std::vector<std::string>& LINES);
		std::vector<TOKEN> get_tokens()
		{
			return this->TOKENS;
		}
	private:
		std::string TXT;
		std::vector<std::string> LINES;
		std::vector<TOKEN> TOKENS;
		std::string CUR_TOK;

		// state
		int position = 0;
		int cycle = 0;
		bool in_string = false;


		char CURRENT()
		{
			if (this->position > this->TXT.size())
				return '\0';
			return this->TXT[this->position];
		}

		void ADVANCE()
		{
			this->position++;
		}

		void ADVANCE_NEXT_TXT()
		{
			this->ADD_CUR_TOK();
			this->position = 0;
			this->cycle++;
			if (this->cycle < this->LINES.size())
			{
				// will advance to next line
				this->TXT = this->LINES[this->cycle];
				this->CUR_TOK = "";
			}
		}

		// TOKEN
		void ADD_CUR_TOK();
		void ADD_TOKEN(TOKEN_TYPES TYPE);
};