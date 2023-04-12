/*
* The main entry point of the program
* Contains function for controlling the interpreter core
*/
#include <iostream>
#include <vector>
#include "../Interface/console.h"
#include "controller.h"
#include "../Parse/Lexer/tokenizer.h"

void controller::pass_input(std::vector<std::string> LINES)
{
	std::cout << "PARSING..\n";
	// lexer & parser stage
	LEXER lexer(LINES);

	std::cout << "OUTPUT:\n";
	// interpreting stage
}

int main(int argc, char* argv[])
{
	// initialize the interface
	console::init(argc, argv);

}