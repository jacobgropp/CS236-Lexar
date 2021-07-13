#pragma once
#include "String.h"
#include "Header.h"
#include "Row.h"
#include "Id.h"
#include "Query.h"
#include "HeadPredicate.h"
#include <set>

class Relation {
private:
	//Id name;
	string name;
	Header header;
	set<Row> rows;
	
public:
	Relation(string name, Header header);
	Relation(string name, Header header, set<Row> rows);
	Relation() {};
	~Relation();

	void addRow(Row row);

	Relation execute(Predicate query);

	Relation select(vector<int> indeces, vector<string> value);
	Relation select(vector<int> firstMatch, vector<int> secondMatch);
	Relation project(vector<int> indeces);
	Relation rename(vector<string> values);

	Relation naturalJoin(Relation newRelation);
	Relation relationUnion(Relation unionRelation);

	vector<int> findIndeces(HeadPredicate headPredicate);

	string getName();
	Header getHeader();
	set<Row> getRows();

	string toString();
	string toOutputString();
};
