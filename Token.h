#pragma once
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

enum TokenType{ COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, WHITESPACE, UNDEFINED, EoF};


class Token{
private: 
	/*
	 *A tokenType as specified in the project specs
	 */
	TokenType tokenType;
	/*
	 *A string extracted from the file text
	 */
	string tokenValue;
	/*
	 *A number - the line the token started on in the file
	 */
	int lineNumber;

public:
//Constructor
	Token(string tokenValue, TokenType tokenType, int lineNumber);
	Token();

//Destructor
	~Token();

//Commands
	string tokenTypeToString(TokenType tokenType);

//Queries
	//Getters
	TokenType getTokenType();
	string getTokenValue();
	int getLineNumber();

	//toStrings
	string toString();

};
