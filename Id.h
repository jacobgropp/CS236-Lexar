#pragma once

#include "Lexer.h"
#include "Parameter.h"

class Id : public Parameter {
private:
	Token id;
public:
	Id(Lexer &lexer);
	Id() {}
	~Id();

	virtual string toString();

	string getIdValue();

};