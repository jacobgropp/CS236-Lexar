#pragma once

#include "Fact.h"

using namespace std;

class Facts {
private:
	vector<Fact> facts;
	vector<string> domain;
public:
	Facts(Lexer &lexer);
	Facts();
	~Facts();

	string toString();

	vector<Fact> getFacts();
	vector<string> getDomain();
};