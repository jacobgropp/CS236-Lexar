#include "Lexer.h"

//Constructor
Lexer::Lexer(InputChars& inputFile)
{
	totalTokens = 0;
	index = 0;
	while (!inputFile.EoFCheck()) {
		inputFile.checkForSpace();
		if (inputFile.EoFCheck()) break;

		switch (inputFile.getCurrentChar()) {
		case ',': {
			currentToken = COMMA;
			createTOKEN(",", inputFile.getCurrentLine());
			break;
		}
		case '.': {
			currentToken = PERIOD;
			createTOKEN(".", inputFile.getCurrentLine());
			break;
		}
		case '?': {
			currentToken = Q_MARK;
			createTOKEN("?", inputFile.getCurrentLine());
			break;
		}
		case '(': {
			currentToken = LEFT_PAREN;
			createTOKEN("(", inputFile.getCurrentLine());
			break;
		}
		case ')': {
			currentToken = RIGHT_PAREN;
			createTOKEN(")", inputFile.getCurrentLine());
			break;
		}
		case ':': {
			if (inputFile.nextChar('-')) {
				currentToken = COLON_DASH;
				createTOKEN(":-", inputFile.getCurrentLine());
				inputFile.advanceInput();
			}
			else {
				currentToken = COLON;
				createTOKEN(":", inputFile.getCurrentLine());
			}
			break;
		}
		case '*': {
			currentToken = MULTIPLY;
			createTOKEN("*", inputFile.getCurrentLine());
			break;
		}
		case '+': {
			currentToken = ADD;
			createTOKEN("+", inputFile.getCurrentLine());
			break;
		}
		case '#': {
			currentToken = COMMENT;
			if (inputFile.nextChar('|')) {
				makeBlockComment(inputFile);
			}
			else
				makeComment(inputFile);
			break;
		}
		case '\'':
		{
			currentToken = STRING;
			makeString(inputFile);
			break;
		}
		case '&':
		case '^':
		case '$':
		{
			currentToken = UNDEFINED;
			stringstream ss;
			string convertChar = "";
			ss << inputFile.getCurrentChar();
			ss >> convertChar;
			createTOKEN(convertChar, inputFile.getCurrentLine());
			break;
		}
		default: {
			createID(inputFile);
			break;
		}
		}
		inputFile.advanceInput();
	}
	currentToken = EoF;
	createTOKEN("", inputFile.getCurrentLine());
}

//Deconstructor
Lexer::~Lexer() {}

//Commands

//Creators
void Lexer::createTOKEN(string value, int lineNumber){
	Token newToken(value, currentToken, lineNumber);
	storedTokens.push_back(newToken);
	totalTokens++;
}

//Specialized Commands
void Lexer::makeComment(InputChars& inputFile){
	string newComment = "#";
	inputFile.advanceInput();
	while (inputFile.getCurrentChar() != '\n'){
		if (inputFile.EoFCheck()){
			createTOKEN(newComment, inputFile.getCurrentLine());
			return;
		}
		else {
			if (isspace(inputFile.getCurrentChar())){
				switch (inputFile.getCurrentChar()) {
				case '\t': {
					newComment += '\t';
					break;
				}
				case ' ': {
					newComment += ' ';
					break;
				}
				}
			}
			string convertChar = "";
			stringstream ss;
			ss << inputFile.getCurrentChar();
			ss >> convertChar;
			newComment += convertChar;
			inputFile.advanceInput();
		}
	}
	//createTOKEN(newComment, inputFile.getCurrentLine());
	inputFile.incrementCurrentLine();
	return;
}

void Lexer::makeBlockComment(InputChars& inputFile){
	string newComment = "#|";
	inputFile.advanceInput();
	int currentLine = 0;
	inputFile.advanceInput();
	while (inputFile.getCurrentChar() != '|' || !inputFile.nextChar('#')){
		if (!inputFile.EoFCheck()){
			if (isspace(inputFile.getCurrentChar())) {
				switch (inputFile.getCurrentChar()) {
				case '\t': {
					newComment += '\t';
					break;
				}
				case '\n': {
					newComment += '\n';
					currentLine++;
					break;
				}
				case ' ': {
					newComment += ' ';
					break;
				}
				}
			}
			string convertChar = "";
			stringstream ss;
			ss << inputFile.getCurrentChar();
			ss >> convertChar;
			newComment += convertChar;
			inputFile.advanceInput();
		}
		else{
			if (inputFile.getCurrentChar() == '|') {
				newComment += '|';
			}
			currentToken = UNDEFINED;
			createTOKEN(newComment, inputFile.getCurrentLine());
			for (int i = 0; i < currentLine; i++) {
				inputFile.incrementCurrentLine();
			}
			return;
		}
	}
	if (inputFile.nextChar('#')) {
		newComment += '|';
		inputFile.advanceInput();
		newComment += '#';
		//createTOKEN(newComment, inputFile.getCurrentLine());
	}
	else {
		newComment += '|';
		inputFile.advanceInput();
		currentToken = UNDEFINED;
		createTOKEN(newComment, inputFile.getCurrentLine());
		inputFile.incrementCurrentLine();
	}
	for (int i = 0; i < currentLine; i++){
		inputFile.incrementCurrentLine();
	}
	return;
}

void Lexer::makeString(InputChars& inputFile){
	string newString = "\'";
	inputFile.advanceInput();
	int currentLine = 0;
	while (inputFile.getCurrentChar() != '\'' | inputFile.nextChar('\'')) {
		if (isspace(inputFile.getCurrentChar())) {
			switch (inputFile.getCurrentChar()) {
			case '\t': {
				newString += '\t';
				break;
			}
			case '\n': {
				newString += '\n';
				currentLine++;
				break;
			}
			case ' ': {
				newString += ' ';
				break;
			}
			}
		}
		if (!inputFile.EoFCheck()) {
			if (inputFile.getCurrentChar() == '\'' && inputFile.nextChar('\'')) {
				newString += '\'';
				inputFile.advanceInput();
			}
			string convertChar = "";
			stringstream ss;
			ss << inputFile.getCurrentChar();
			ss >> convertChar;
			newString += convertChar;		
			inputFile.advanceInput();
		}
		else {
			currentToken = UNDEFINED;
			createTOKEN(newString, inputFile.getCurrentLine());
			for (int i = 0; i < currentLine; i++) {
				inputFile.incrementCurrentLine();
			}
			return;
		}
	}
	newString += '\'';
	createTOKEN(newString, inputFile.getCurrentLine());
	for (int i = 0; i < currentLine; i++) {
		inputFile.incrementCurrentLine();
	}
	return;
}

void Lexer::createID(InputChars& inputFile) {
	string id;
	string convertChar = "";
	stringstream ss;
	ss << inputFile.getCurrentChar();
	ss >> convertChar;
	id += convertChar;
	if (isalpha(inputFile.getCurrentChar())) {
		if (!(isalpha(inputFile.nextChar()) | isdigit(inputFile.nextChar()))) {
			IDDeterminer(inputFile, id);
			return;
		}
		inputFile.advanceInput();
		while ((isalpha(inputFile.getCurrentChar()) | isdigit(inputFile.getCurrentChar())) && !inputFile.EoFCheck()) {
			string convertChar = "";
			stringstream ss;
			ss << inputFile.getCurrentChar();
			ss >> convertChar;
			id += convertChar;
			if (!(isspace(inputFile.nextChar()))
				&& (isalpha(inputFile.nextChar()) | isdigit(inputFile.nextChar()))) {
				inputFile.advanceInput();
			}
			else break;
		}
		IDDeterminer(inputFile, id);
	}
	else {
		currentToken = UNDEFINED;
		createTOKEN(id, inputFile.getCurrentLine());
	}
}

void Lexer::IDDeterminer(InputChars& inputFile, string id){
	if (id == "Schemes") {
		currentToken = SCHEMES;
		createTOKEN(id, inputFile.getCurrentLine());
	}
	else if (id == "Facts") {
		currentToken = FACTS;
		createTOKEN(id, inputFile.getCurrentLine());
	}
	else if (id == "Rules") {
		currentToken = RULES;
		createTOKEN(id, inputFile.getCurrentLine());
	}
	else if (id == "Queries") {
		currentToken = QUERIES;
		createTOKEN(id, inputFile.getCurrentLine());
	}
	else {
		currentToken = ID;
		createTOKEN(id, inputFile.getCurrentLine());
	}
}

void Lexer::increaseIndex() {
	index++;
}
//Queries

//Getters
TokenType Lexer::getCurrentToken(){
	return currentToken;
}  

int Lexer::getTotalToken(){
	return totalTokens;
}

vector<Token> Lexer::getStoredTokens() {
	return storedTokens;
}

int Lexer::getIndex() {
	return index;
}

Token Lexer::match(TokenType tokenType) {
	Token result = top();
	TokenType resultType = result.getTokenType();
	if ((resultType == EoF && tokenType != EoF) || resultType != tokenType) throw result;
	//index++;
	pop();
	return result;
}

Token Lexer::top() {
	Token top = storedTokens.front();
	return top;
}

void Lexer::pop() {
	storedTokens.erase(storedTokens.begin());
	return;
}

//toString
void Lexer::toString(){
	for (int i = 0; i < totalTokens; i++){
		cout << storedTokens[i].toString();
		cout << endl;
	}
	cout << "Total Tokens = " << totalTokens << endl;
}
