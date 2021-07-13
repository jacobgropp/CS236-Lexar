#include "Scheme.h"

Scheme::Scheme(Lexer &lexer) {
	
	schemeId = Id(lexer);
	lexer.match(LEFT_PAREN);
	columnNames.push_back(Id(lexer));
	while (lexer.top().getTokenType() == COMMA) {
		lexer.pop();
		columnNames.push_back(Id(lexer));
	}
	lexer.match(RIGHT_PAREN);
}

Scheme::~Scheme() {}

string Scheme::getRelationName() {
	return schemeId.getIdValue();
}

Header Scheme::getHeader() {
	Header result;
	for (int i = 0; i < columnNames.size(); i++) {
		result.push_back(columnNames[i].toString());
	}
	return result;
}

string Scheme::toString() {
	stringstream ss;
	ss << schemeId.toString();
	ss << "(";
	for (int i = 0; i < columnNames.size(); i++) {
		if (i == columnNames.size() - 1)
			ss << columnNames[i].toString();
		else
			ss << columnNames[i].toString() << ",";
	}
	ss << ")";// << endl;
	return ss.str();
}