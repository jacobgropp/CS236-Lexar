#pragma once

#include "Parameter.h"
#include "Id.h"
//#include "Database.h"
//#include "Relation.h"

class Relation;

class Predicate : public Parameter {
private:
	Id predicateId;
	vector<Parameter*> parameters;

public:
	Predicate(Lexer &lexer);
	Predicate() {}
	~Predicate();

	string getPredicateId();
	vector<Parameter*> getParameters();

	string queryOutput(Relation relation);
	string toString();
};

