#include "Expression.h"
//#include "Parameter.h"

Expression::Expression(Lexer &lexer) {
	lexer.match(LEFT_PAREN);
	parameter1 = Parameter().createParameter(lexer);
	switch (lexer.top().getTokenType()) {
	case(MULTIPLY): {
		signIndicator = true;
		lexer.match(MULTIPLY);
		break;
	}
	case(ADD): {
		signIndicator = false;
		lexer.match(ADD);
		break;
	}
	}
	parameter2 = Parameter().createParameter(lexer);
	lexer.match(RIGHT_PAREN);
}

Expression::~Expression() {}

string Expression::toString() {
	stringstream ss;
	if (signIndicator)
		ss << "(" << parameter1->toString() << "*" << parameter2->toString() << ")";
	else 
		ss << "(" << parameter1->toString() << "+" << parameter2->toString() << ")";
	return ss.str();
}