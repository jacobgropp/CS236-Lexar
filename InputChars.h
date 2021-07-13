#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

class InputChars{
private:
	ifstream inFile;
	char currentChar;
	int currentLine;

public:
	InputChars(string filename);
	~InputChars();

//Commands

	void advanceInput();
	void checkForSpace();
	void incrementCurrentLine();
	char nextChar();

//Queries
	//Getters
	char getCurrentChar();
	int getCurrentLine();

	//Bools
	bool nextChar(char givenChar);
	bool EoFCheck();
};