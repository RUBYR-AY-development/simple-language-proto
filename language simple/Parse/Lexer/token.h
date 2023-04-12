#pragma once
#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>

enum class TOKEN_TYPES
{
	EOL, // end of line
	_EOF_, // end of file
	LEFT_PAREN, // (
	RIGHT_PAREN, // )
	QUOTATION_DOUBLE, // "
	QUOTATION_SINGLE, // '
	DOT, // .
	SEMICOLON, // ;
	COLON, // :
	PLUS, // +
	MINUS, // -
	STAR, // *
	FRONT_SLASH, // /
	GREATER_THAN, // >
	LESS_THAN, // <
	EQUAL, // =
	COMMA, // ,
	LEFT_CURLY_BRACE, // {
	RIGHT_CURLY_BRACE, // }
};

struct TOKEN
{
	std::string type;
	std::string value;

	auto operator<=>(const TOKEN&) const = default;
};
