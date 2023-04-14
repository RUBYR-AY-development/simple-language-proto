/*
* This recieves input from the console, and sends the input
*/

#include <iostream>
#include <vector>
#include <string>
#include "console.h"
#include "../Util/types.h"
#include "../Parse/Lexer/tokenizer.h"
#include "../Main/controller.h"

constexpr raw_str LANG_INFO = "[no name] Language; Version: 0 (IN-DEVELOPMENT)";


// prints the info about the program
void print_info()
{
	std::cout << LANG_INFO << std::endl;
}

// input reciever
void recieve_inputs()
{
	std::vector<std::string> inputs;
	std::string INPUT_BUF;
	while (true)
	{
		std::cout << ">>> "; getline(std::cin, INPUT_BUF);
		if (INPUT_BUF != "EOF")
			inputs.push_back(INPUT_BUF);
		else
			break;
	}

	controller::pass_input(inputs);
	recieve_inputs();
}

void console::init(int argc, char* argv[])
{
	print_info();
	recieve_inputs();
}