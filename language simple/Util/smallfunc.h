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

inline bool string_is_integer(std::string& STRING)
{
    for (char const& ch : STRING) {
        if (std::isdigit(ch) == 0)
            return false;
    }
    return true;
}

inline bool string_is_float(std::string& STRING)
{
    // idk how efficient it is but tell me if its horribly inefficient
    bool VALID;
    std::string::size_type sz;
    try
    {
        std::stod(STRING, &sz);
        VALID = true;
    }
    catch (std::exception& ia)
    {
        VALID = false;
    }
    return VALID;
}