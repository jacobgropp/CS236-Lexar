#include "Query.h"

Query::Query(Lexer &lexer) : Predicate(lexer) {
	lexer.match(Q_MARK);
}

Query::~Query() {}

string Query::toString() {
	stringstream ss;
	ss << Predicate::toString();
	ss << "?";

	return ss.str();
}

