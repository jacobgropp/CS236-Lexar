#pragma once

#include "Lexer.h"
#include "HeadPredicate.h"
#include "Predicate.h"

class Rule {
private:
	HeadPredicate head;
	vector<Predicate> predicates;

public:
	Rule(Lexer &lexer);
	~Rule();

	//Getters
	HeadPredicate getHead();
	vector<Predicate> getPredicates();

	string toString();
};

