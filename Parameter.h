#pragma once
#include "Lexer.h"

using namespace std;

class Parameter {
public:
	Parameter();
	~Parameter();
	static Parameter* createParameter(Lexer &lexer);
	virtual string toString() { return ""; }
};