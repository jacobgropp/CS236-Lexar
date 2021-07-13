#include "HeadPredicate.h"

HeadPredicate::HeadPredicate(Lexer &lexer) {
	headId = Id(lexer);
	lexer.match(LEFT_PAREN);
	params.push_back(Id(lexer));
	while (lexer.top().getTokenType() == COMMA) {
		lexer.pop();
		params.push_back(Id(lexer));
	}
	lexer.match(RIGHT_PAREN);
}

HeadPredicate::~HeadPredicate() {}

string HeadPredicate::getHeadId() {
	return headId.toString();
}

vector<Id> HeadPredicate::getParams() {
	return params;
}

string HeadPredicate::toString() {
	stringstream ss;
	ss << headId.toString();
	ss << "(";
	for (int i = 0; i < params.size(); i++) {
		if (i == params.size() - 1)
			ss << params[i].toString();
		else
			ss << params[i].toString() << ",";
	}
	ss << ")";
	return ss.str();
}