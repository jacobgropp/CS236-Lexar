#include "Rules.h"

Rules::Rules(Lexer &lexer) {
	lexer.match(RULES);
	lexer.match(COLON);
	while (lexer.top().getTokenType() == ID) {
		rules.push_back(Rule(lexer));
	}
}

Rules::~Rules() {}

vector<Rule> Rules::getRules() {
	return rules;
}

string Rules::toString() {
	stringstream ss;
	ss << "Rules(" << rules.size() << "):" << endl;
	for (int i = 0; i < rules.size(); i++) {
		ss << "  " << rules[i].toString() << endl;
	}
	ss << endl;
	return ss.str();
}