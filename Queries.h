#pragma once

#include "Lexer.h"
#include "Query.h"

class Queries {
private:
	vector<Query> queries;
public:
	Queries(Lexer &lexer);
	Queries();
	~Queries();

	vector<Query> getQueries();

	string toString();
};