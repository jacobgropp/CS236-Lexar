#include "Schemes.h"

Schemes::Schemes(Lexer &lexer) {
	lexer.match(SCHEMES);
	lexer.match(COLON);
	do {
		schemes.push_back(Scheme(lexer));
	} while (lexer.top().getTokenType() == ID);
}

Schemes::~Schemes() {}

vector<Scheme> Schemes::getSchemes() {
	return schemes;
}

string Schemes::toString() {
	stringstream ss;
	ss << "Schemes(" << schemes.size() << "):" << endl;
	for (int i = 0; i < schemes.size(); i++) {
		ss << "  " << schemes[i].toString() << endl;
	}
	ss << endl;
	return ss.str();
}

