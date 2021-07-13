#pragma once

#include "Lexer.h"
#include "Id.h"
#include "Header.h"

class Scheme {
private:
	Id schemeId;
	vector<Id> columnNames;
public:
	Scheme(Lexer &lexer);
	~Scheme();

	string getRelationName();
	Header getHeader();
	virtual string toString();
};