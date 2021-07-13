#include "String.h"

String::String(Lexer &lexer) {
	string = lexer.match(STRING);
}

String::~String() {}

string String::toString() {
	stringstream ss;
	ss << string.getTokenValue();
	return ss.str();
}