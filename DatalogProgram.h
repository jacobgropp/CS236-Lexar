#pragma once
#include <algorithm>

#include "Schemes.h"
#include "Facts.h"
#include "Rules.h"
#include "Queries.h"

class DatalogProgram {
	friend class Fact;
private:
	Schemes* schemes;
	Facts* facts;
	Rules* rules;
	Queries* queries;
	vector<string> domain;

public:
	DatalogProgram(Lexer &lexer);
	~DatalogProgram();

	Schemes* getSchemes();
	Facts* getFacts();
	Rules* getRules();
	Queries* getQueries();

	string toString();

};