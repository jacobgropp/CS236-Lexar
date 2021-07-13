#include "Queries.h"

Queries::Queries(Lexer &lexer) {
	lexer.match(QUERIES);
	lexer.match(COLON);
	do {
		queries.push_back(Query(lexer));
	} while (lexer.top().getTokenType() == ID);
}

Queries::~Queries() {}

vector<Query> Queries::getQueries() {
	return queries;
}

string Queries::toString() {
	stringstream ss;
	ss << "Queries(" << queries.size() << "):" << endl;;
	for (int i = 0; i < queries.size(); i++) {
		ss << "  " << queries[i].toString() << endl;
	}
	ss << endl;
	return ss.str();
}