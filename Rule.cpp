#include "Rule.h"

Rule::Rule(Lexer &lexer) {
	head = HeadPredicate(lexer);
	lexer.match(COLON_DASH);
	predicates.push_back(Predicate(lexer));
	while (lexer.top().getTokenType() == COMMA) {
		lexer.pop();
		predicates.push_back(Predicate(lexer));
	}
	lexer.match(PERIOD);
}

Rule::~Rule() {}

HeadPredicate Rule::getHead() {
	return head;
}

vector<Predicate> Rule::getPredicates() {
	return predicates;
}

string Rule::toString() {
	stringstream ss;
	ss << head.toString() << " :- ";
	for (int i = 0; i < predicates.size(); i++) {
		if (i == predicates.size() - 1 ) 
			ss << predicates[i].toString();
		else
			ss << predicates[i].toString() << ",";
	}
	ss << ".";

	return ss.str();
}
