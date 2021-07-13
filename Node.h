#pragma once
#include <iostream>
#include <string>
#include <set>
#include <sstream>

using namespace std;

class Node {
private:
	int ruleNumber;
	set<int> connections;
	bool processed;
public:
	//Constructors and Deconstructor
	Node() {}
	Node(int ruleNumber, set<int> connections);
	~Node() {}
	//Simple Class Methods
	void addConnections(int i);
	void process();
	//Getters
	int getRuleNumber();
	set<int> getConnections();
	bool getProcessed();
	//ToString
	string toString();
};
