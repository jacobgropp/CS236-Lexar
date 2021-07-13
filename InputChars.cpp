#include "InputChars.h"

//Constructor
InputChars::InputChars(string fileName)
{
	currentLine = 1;
	inFile.open(fileName);
	if (!inFile.is_open())
	{
		cout << "ERROR: File was not opened correctly\n";
	}
	currentChar = inFile.get();
}

//Destructor
InputChars::~InputChars() {}

//Commands
void InputChars::advanceInput(){
	currentChar = inFile.get();
	return;
}
void InputChars::checkForSpace(){
	while (isspace(currentChar)){
		if (currentChar == '\n'){
			currentLine++;
		}
		currentChar = inFile.get();
		if (EoFCheck()) break;
	}
	return;
}
void InputChars::incrementCurrentLine(){
	currentLine++;
	return;
}

//Queries

//Getters
char InputChars::getCurrentChar(){
	return currentChar;
}
int InputChars::getCurrentLine(){
	return currentLine;
}
char InputChars::nextChar(){
	return inFile.peek();
}

//Bools
bool InputChars::nextChar(char givenChar){
	if (inFile.peek() == givenChar)
		return true;
	else
		return false;
}
bool InputChars::EoFCheck(){
	if (inFile.eof()) return true;
	else return false;
}