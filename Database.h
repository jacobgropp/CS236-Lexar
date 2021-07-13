#pragma once
#include "Relation.h"
#include "DatalogProgram.h"
#include <map>


class Database {
private:
	map<string, Relation> relations; 

public:
	Database();

	void addRelation(Scheme scheme);
	void addRowToRelation(Fact fact);

	void addRowsFromRules(Rule rule);

	int getNumberOfFacts();

	Relation getRelation(string name);
};
