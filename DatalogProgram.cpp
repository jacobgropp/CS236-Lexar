#include "DatalogProgram.h"

DatalogProgram::DatalogProgram(Lexer &lexer) {
	schemes = new Schemes(lexer);
	facts = new Facts(lexer);
	rules = new Rules(lexer);
	queries = new Queries(lexer);
}

DatalogProgram::~DatalogProgram() {}

Schemes* DatalogProgram::getSchemes() {
	return schemes;
}
Facts* DatalogProgram::getFacts() {
	return facts;
}
Rules* DatalogProgram::getRules() {
	return rules;
}
Queries* DatalogProgram::getQueries() {
	return queries;
}

string DatalogProgram::toString() {
	stringstream ss;
	ss << schemes->toString();
	ss << facts->toString();
	ss << rules->toString();
	ss << queries->toString();
	domain = facts->getDomain();
	ss << "Domain(" << domain.size() << "):" << endl;
	for (int i = 0; i < domain.size(); i++) {
		ss << "  " << domain[i] << endl;
	}
	return ss.str();
}