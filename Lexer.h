#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

#include "Token.h"
#include "InputChars.h"

using namespace std;

class Lexer{
private:
	/*
	*the current token upon which the lexer is focusing
	*/
	TokenType currentToken;
	/*
	*the total amount of tokens currently stored in the lexer's vector variable
	*/
	int totalTokens;
	/*
	*the library of tokens found in the input file
	*/
	vector<Token> storedTokens;
	/*
	*the index used by the DatalogProgram to parse through the storedTokens vector
	*/
	int index;

public:
//Constructor
	Lexer(InputChars& inputFile);
//Destructor
	~Lexer();
//Commands
	//TokenCreators
	void createTOKEN(string value, int lineNumber);

	//Specialized Commands
	void makeComment(InputChars& inputFile);
	void makeBlockComment(InputChars& inputFile);
	void makeString(InputChars& inputFile);
	void createID(InputChars& inputFile);
	void IDDeterminer(InputChars& inputFile, string id);

	void increaseIndex();

//Queries
	//Getters
	TokenType getCurrentToken();
	int getTotalToken();
	vector<Token> getStoredTokens();
	Token match(TokenType tokenType);
	Token top();
	void pop();
	int getIndex();

	//toStrings
	void toString();
};
