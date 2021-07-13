#pragma once
#include "Lexer.h"
#include "Parameter.h"

class String : public Parameter {
private:
	Token string;
public:
	String(Lexer &lexer);
	String() {}
	~String();

	virtual std::string toString();
};
