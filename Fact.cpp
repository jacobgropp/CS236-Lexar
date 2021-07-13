#include "Fact.h"

Fact::Fact(Lexer &lexer) {
	factID = Id(lexer);
	lexer.match(LEFT_PAREN);
	strings.push_back(String(lexer));
	while (lexer.top().getTokenType() == COMMA) {
		lexer.pop();
		String myString = String(lexer);
		strings.push_back(myString);
	}
	lexer.match(RIGHT_PAREN);
	lexer.match(PERIOD);
}

Fact::~Fact() {}

string Fact::getFactId() {
	return factID.toString();
}

Row Fact::getNewRow() {
	Row newRow;
	for (int i = 0; i < strings.size(); i++) {
		newRow.push_back(strings[i].toString());
	}
	return newRow;
}

string Fact::toString() {
	stringstream ss;
	ss << factID.toString() << "(";
	for (int i = 0; i < strings.size(); i++) {
		if (i == strings.size() -1) 
			ss << strings[i].toString();
		else
			ss << strings[i].toString() << ",";
	}
	ss << ").";

	return ss.str();
}

string Fact::domainToString() {
	stringstream ss;
	ss << "Domain(" << strings.size() << ")";
	for (int i = 0; i < strings.size(); i++) {
		ss << strings[i].toString() << endl;
	}
	return ss.str();
}

vector<String> Fact::getDomain() {
	return strings;
}