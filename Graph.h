#pragma once
#include "Node.h"
#include "Rule.h"
#include <map>
#include <vector>

class Graph {
protected: 
	map<int, Node> nodes;
	vector<int> topologicalOrdering;
	vector<set<int>> stronglyConnectedComponents;
	set<int> SCC;
public:
	//Constructor and Deconstructor
	Graph();
	~Graph();
	//Simple Class Methods
	void addNode(Node newNode);
	void addConnections(int connection, int key);
	void processNode(int key);
	//Rule Dependency Algorithm
	Graph invertGraph();
	void topologicalOrder();
	void processStrongConnections(vector<int> newTopologicalOrdering);
	void depthFirstSearch(Node node, bool SCCTest);
	//Getters
	map<int, Node> getNodes();
	vector<int> getTopologicalOrdering();
	vector<set<int>> getStronglyConnectedComponents();
	//ToStrings
	string toString();
	string printTopologicalOrdering();
	string printStronglyConnectedComponents();
};
