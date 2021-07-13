#pragma once

#include "Lexer.h"
#include "Predicate.h"

class Query : public Predicate {
public:
	Query(Lexer &lexer);
	~Query();

	virtual string toString();
};
