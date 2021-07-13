#include "Predicate.h"
#include "Relation.h"
#include "Database.h"

Predicate::Predicate(Lexer &lexer) {
	predicateId = Id(lexer);
	lexer.match(LEFT_PAREN);
	parameters.push_back(Parameter().createParameter(lexer));
	while (lexer.top().getTokenType() == COMMA) {
		lexer.pop();
		parameters.push_back(Parameter().createParameter(lexer));
	}
	lexer.match(RIGHT_PAREN);
}

Predicate::~Predicate() {}

string Predicate::getPredicateId() {
	return predicateId.getIdValue();
}

vector<Parameter*> Predicate::getParameters() {
	return parameters;
}


string Predicate::queryOutput(Relation relation) {
	stringstream ss;
	bool outputVariables = false;
	for (int i = 0; i < parameters.size(); i++) {
		if (parameters[i]->toString().at(0) != '\'') {
			outputVariables = true;
		}
	}
	if (relation.getRows().size() == 0) {
		ss << " No" << endl;
	}
	else {
		ss << " Yes(" << relation.getRows().size() << ")" << endl;
	}
	if (outputVariables) {
		for (auto iterator : relation.getRows()) {
			ss << "  ";
			for (int i = 0; i < iterator.size(); i++) {
				ss << relation.getHeader()[i] << "=" << iterator[i];
				if (i != iterator.size() - 1) {
					ss << ", ";
				}
			}
			ss << endl;
		}
	}
	return ss.str();
}

string Predicate::toString() {
	stringstream ss;
	ss << predicateId.toString() << "(";
	for (int i = 0; i < parameters.size(); i++) {
		if (i == parameters.size() - 1 ) 
			ss << parameters[i]->toString();
		else 
			ss << parameters[i]->toString() << ",";
	}
	ss << ")";

	return ss.str();
}
