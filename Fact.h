#pragma once
#include <vector>

#include "Id.h"
#include "String.h"
#include "Lexer.h"
#include "Row.h"

using namespace std;

class Fact {
private:
	Id factID;
	vector<String> strings;
public:
	Fact(Lexer &lexer);
	~Fact();

	string getFactId();
	Row getNewRow();

	string toString();
	string domainToString();

	vector <String> getDomain();
};