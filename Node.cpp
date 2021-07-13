#include "Node.h"

//Constructor
Node::Node(int ruleNumber, set<int> connections) {
	this->ruleNumber = ruleNumber;
	this->connections = connections;
	processed = false;
}
//Simple Class Methods
void Node::addConnections(int i) {
	connections.insert(i);
}

void Node::process() {
	processed = true;
}
//Getters
int Node::getRuleNumber() {
	return ruleNumber;
}

set<int> Node::getConnections() {
	return connections;
}

bool Node::getProcessed() {
	return processed;
}
//ToString
string Node::toString() {
	stringstream ss;
	ss << "R" << ruleNumber
		<< " { ";
	for (auto components : connections) {
		ss << components << " ";
	}
	ss << "}" << endl;
	return ss.str();
}