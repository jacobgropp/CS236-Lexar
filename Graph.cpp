#include "Graph.h"

//Constructor and Deconstructor
Graph::Graph() {}
Graph::~Graph() {}

//Simple Class Methods
void Graph::addNode(Node newNode) {
	nodes.insert(pair<int, Node>(newNode.getRuleNumber(), newNode));
}

void Graph::addConnections(int connection, int key) {
	nodes.find(key)->second.addConnections(connection);
}

void Graph::processNode(int key) {
	nodes[key].process();
}

//Rule Dependency Algorithm
Graph Graph::invertGraph() {
	Graph newGraph;
	//Add all rules to newGraph
	for (int i = 0; i < nodes.size(); i++) {
		Node newNode(i, {});
		newGraph.addNode(newNode);
	}
	//Add new, inverted components to newGraph
	for (int connection = 0; connection < nodes.size(); connection++) {
		Node connectingNode = nodes.find(connection)->second;
		for (auto key : connectingNode.getConnections()) {
			newGraph.addConnections(connection, key);
		}
	}
	return newGraph;
}

void Graph::topologicalOrder() {
	bool SCCTest = false;
	//Process a DFS on each node to find the topological order
	for (auto& x : nodes) {
		depthFirstSearch(x.second, SCCTest);
	}
}

void Graph::processStrongConnections(vector<int> newTopologicalOrdering) {
	this->topologicalOrdering = newTopologicalOrdering;
	bool SCCTest = true;
	//Reverse the topological ordering and run a DFS on each node to find the strongly connected components
	for (auto i = topologicalOrdering.rbegin(); i != topologicalOrdering.rend(); ++i) {
		if (!nodes[*i].getProcessed()) {
			depthFirstSearch(nodes[*i], SCCTest);
			stronglyConnectedComponents.push_back(SCC);
			SCC.clear();
		}
	}
}

void Graph::depthFirstSearch(Node node, bool SCCTest) {
	if (!node.getProcessed()) {
		processNode(node.getRuleNumber());
		for (auto i : node.getConnections()) {
			depthFirstSearch(nodes[i], SCCTest);
		}
		//add rule number to SCC placeholder set or topological ordering vector
		if (SCCTest) {
			SCC.insert(node.getRuleNumber());
		}
		else {
			topologicalOrdering.push_back(node.getRuleNumber());
		}
	}
}

//Getters
map<int, Node> Graph::getNodes() {
	return nodes;
}

vector<int> Graph::getTopologicalOrdering() {
	return topologicalOrdering;
}

vector<set<int>> Graph::getStronglyConnectedComponents() {
	return stronglyConnectedComponents;
}

//ToStrings
string Graph::toString() {
	stringstream ss;
	for (auto i : nodes) {
		ss << i.second.toString();
	}
	ss << endl;
	return ss.str();
}

string Graph::printTopologicalOrdering() {
	stringstream ss;
	ss << "Topological Ordering: ";
	ss << "{ ";
	for (int i = 0; i < topologicalOrdering.size(); i++) {
		ss << topologicalOrdering[i] << " ";
	}
	ss << "}" << endl;
	return ss.str();
}

string Graph::printStronglyConnectedComponents() {
	stringstream ss;
	ss << "Strongly Connected Components:" << endl;
	for (int i = 0;  i < stronglyConnectedComponents.size(); i++) {
		ss << "{ ";
		for (auto j : stronglyConnectedComponents[i]) {
			ss << "R" << j << " ";
		}
		ss << "}" << endl;
	}
	ss << endl;
	return ss.str();
}

//Helper functions
string printSet(set<int> SET) {
	stringstream ss;
	ss << "{ ";
	for (auto i : SET) {
		ss << i << " ";
	}
	ss << "}" << endl;
	return ss.str();
}