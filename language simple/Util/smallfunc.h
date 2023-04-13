/*
* Contains small functions
*/
#pragma once

inline bool is_even(int a)
{
	return (a % 2) == 0;
}

inline void display_err(int line, const char* MESSAGE)
{
    std::cout << "Line " << line << " Syntax error; Msg: ";
    std::cerr << MESSAGE;
    std::exit(1);
}