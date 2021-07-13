#include "Facts.h"
#include <algorithm>

Facts::Facts(Lexer &lexer) {
	lexer.match(FACTS);
	lexer.match(COLON);
	while (lexer.top().getTokenType() == ID) {
		facts.push_back(Fact(lexer));
	}
}

Facts::Facts() {}
Facts::~Facts() {}

vector<Fact> Facts::getFacts() {
	return facts;
}

string Facts::toString() {
	stringstream ss;
	ss << "Facts(" << facts.size() << "):" << endl;
	for (int i = 0; i < facts.size(); i++) {
		ss << "  " << facts[i].toString() << endl;
	}
	ss << endl;
	return ss.str();
}

vector<string> Facts::getDomain() {
	for (int i = 0; i < facts.size(); i++) {
		vector<String> newDomain = facts[i].getDomain();
		for (int i = 0; i < newDomain.size(); i++) {
			domain.push_back(newDomain[i].toString());
		}
	}
	sort(domain.begin(), domain.end());
	domain.erase(unique(domain.begin(), domain.end()), domain.end());
	return domain;
}