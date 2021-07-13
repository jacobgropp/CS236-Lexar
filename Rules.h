#pragma once

#include "Lexer.h"
#include "Rule.h"

class Rules {
private:
	vector<Rule> rules;
public:
	Rules(Lexer &Lexer);
	Rules();
	~Rules();

	vector<Rule> getRules();

	string toString();
};

