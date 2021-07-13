#pragma once

#include "Lexer.h"
#include "Scheme.h"

class Schemes {
private:
	vector<Scheme> schemes;
public:
	Schemes(Lexer &lexer);
	Schemes();
	~Schemes();

	vector<Scheme> getSchemes();

	string toString();
};