#pragma once

#include "Parameter.h"

//class Parameter;
enum Operator { PLUS, STAR };

class Expression : public Parameter {
protected:
	Parameter* parameter1;
	Parameter* parameter2;
	bool signIndicator; 
public:
	Expression(Lexer &lexer);
	~Expression();

	virtual string toString();
};
