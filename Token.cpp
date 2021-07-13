#include "Token.h"

Token::Token(string tokenValue, TokenType tokenType, int lineNumber){
	this->tokenValue = tokenValue;
	this->tokenType = tokenType;
	this->lineNumber = lineNumber;
}
Token::Token() {}

Token::~Token() {}

//Commands
string Token::tokenTypeToString(TokenType tokenType){
	string outString = "";
	switch (tokenType){
	case COMMA:              outString = "COMMA";
		break;
	case PERIOD:             outString = "PERIOD";
		break;
	case Q_MARK:             outString = "Q_MARK";
		break;
	case LEFT_PAREN:         outString = "LEFT_PAREN";
		break;
	case RIGHT_PAREN:        outString = "RIGHT_PAREN";
		break;
	case COLON:              outString = "COLON";
		break;
	case COLON_DASH:         outString = "COLON_DASH";
		break;
	case MULTIPLY:           outString = "MULTIPLY";
		break;
	case ADD:                outString = "ADD";
		break;
	case SCHEMES:            outString = "SCHEMES";
		break;
	case FACTS:              outString = "FACTS";
		break;
	case RULES:              outString = "RULES";
		break;
	case QUERIES:            outString = "QUERIES";
		break;
	case ID:                 outString = "ID";
		break;
	case STRING:			 outString = "STRING";
		break;
	case COMMENT:            outString = "COMMENT";
		break;
	case WHITESPACE:         outString = "WHITESPACE";
		break;
	case UNDEFINED:          outString = "UNDEFINED";
		break;
	case EoF:				 outString = "EOF";
		break;
	}
	return outString;
};
//Queries

//Getters
TokenType Token::getTokenType(){
	return tokenType;
}
string Token::getTokenValue(){
	return tokenValue;
}
int Token::getLineNumber(){
	return lineNumber;
}

//toStrings
string Token::toString(){
	stringstream ss;
	ss << "("
		<< tokenTypeToString(tokenType)
		<< ",\""
		<< tokenValue
		<< "\","
		<< lineNumber
		<< ")";
	return ss.str();
}