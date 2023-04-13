/*
* The main entry point of the program
* Contains function for controlling the interpreter core
*/
#include <iostream>
#include <vector>
#include "../Interface/console.h"
#include "controller.h"
#include "../Parse/Lexer/tokenizer.h"
#include "../Parse/Expression/expr_main.h"

void controller::pass_input(std::vector<std::string> LINES)
{
	std::cout << "PARSING..\n";
	// lexer
	LEXER* lexer = new LEXER(LINES);
	std::vector<TOKEN> TOKENS = lexer->get_tokens();
	delete lexer; // explicitly done with it
	// expression
	expr_main::handle(TOKENS);

	std::cout << "OUTPUT:\n";
	// interpreting stage
}

int main(int argc, char* argv[])
{
	// initialize the interface
	console::init(argc, argv);

}