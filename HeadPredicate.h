#pragma once

#include "Lexer.h"
#include "Id.h"
#include "Header.h"
#include "Predicate.h"

using namespace std;

class HeadPredicate : public Predicate{
private: 
	Id headId;
	vector<Id> params;

public:
	HeadPredicate(Lexer &lexer);
	HeadPredicate() {}
	~HeadPredicate();

	string getHeadId();
	vector<Id> getParams();

	virtual string toString();
};