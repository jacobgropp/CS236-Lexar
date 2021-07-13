#include "Parameter.h"
#include "Expression.h"
#include "Id.h"
#include "String.h"

Parameter::Parameter() {}

Parameter::~Parameter() {}

Parameter* Parameter::createParameter(Lexer &lexer) {
	if (lexer.top().getTokenType() == ID) {
		return new Id(lexer);
	}
	else if (lexer.top().getTokenType() == STRING) {
		return new String(lexer);
	}
	else {
		return new Expression(lexer);
	}
}