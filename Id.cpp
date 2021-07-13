#include "Id.h"

Id::Id(Lexer &lexer) {
	id = lexer.match(ID);
}

Id::~Id() {}

string Id::getIdValue() {
	return id.getTokenValue();
}

string Id::toString() {
	stringstream ss;
	ss << id.getTokenValue();
	return ss.str();
}