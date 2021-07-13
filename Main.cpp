#include "Lexer.h"
#include "DatalogProgram.h"
#include "Relation.h"
#include "Database.h"
#include "Graph.h"

#include <iostream>

string printVector(vector<int> print) {
	stringstream ss;
	ss << "{ ";
	for (int i = 0; i < print.size(); i++) {
		ss << print[i] << " ";
	}
	ss << "}";
	return ss.str();
}

int main(int argc, char *argv[]){
	//try {
	//	InputChars inputFile(argv[1]);
	//	Lexer LexicalAnalyser(inputFile);
	//	DatalogProgram datalogProgram = DatalogProgram(LexicalAnalyser);
	//	//Filling the Database
	//	Database database;
	//	Schemes* datalogProgramSchemes = datalogProgram.getSchemes();
	//	vector<Scheme> datalogProgramSchemeVector = datalogProgramSchemes->getSchemes();
	//	for (int i = 0; i < datalogProgramSchemeVector.size(); i++) {
	//		database.addRelation(datalogProgramSchemeVector[i]);
	//	}
	//	Facts* datalogProgramFacts = datalogProgram.getFacts();
	//	vector<Fact> datalogProgramFactVector = datalogProgramFacts->getFacts();
	//	for (int i = 0; i < datalogProgramFactVector.size(); i++) {
	//		database.addRowToRelation(datalogProgramFactVector[i]);
	//	}
	//	//Adding Facts from Rules
	//	Rules* datalogProgramRules = datalogProgram.getRules();
	//	vector<Rule> datalogProgramRuleVector = datalogProgramRules->getRules();
	//	int numberOfFacts = 0;
	//	bool stopIterations = false;
	//	int count = 0;
	//	do {
	//		numberOfFacts = database.getNumberOfFacts();
	//		for (int i = 0; i < datalogProgramRuleVector.size(); i++) {
	//			database.addRowsFromRules(datalogProgramRuleVector[i]);
	//		}
	//		if (numberOfFacts == database.getNumberOfFacts()) stopIterations = true;
	//		count++;
	//	} while (!stopIterations);
	//	cout << "Schemes populated after " << count << " passes through the Rules." << endl;
	//	//Finding the Queries
	//	Queries* datalogProgramQueries = datalogProgram.getQueries();
	//	vector<Query> datalogProgramQueryVector = datalogProgramQueries->getQueries();
	//	//Answering the Queries
	//	for (int i = 0; i < datalogProgramQueryVector.size(); i++) {
	//		Relation relation = database.getRelation(datalogProgramQueryVector[i].getPredicateId());
	////		Relation resultRelation = relation.execute(datalogProgramQueryVector[i]);
	////		cout << datalogProgramQueryVector[i].toString();
	////		cout << datalogProgramQueryVector[i].queryOutput(resultRelation);
	////	}
	////}
	////catch (Token token) {
	////	cout << "Failure!" << endl;
	////	cout << token.toString() << endl;
	////}
	//TEST CASE 1 - Invert Graph
	cout << "TEST CASE 1: Reverse Graph" << endl;
	Node T1_0(0, { 0, 1 });
	Node T1_1(1, {});
	Node T1_2(2, { 0,1 });
	Graph testCase1;
	testCase1.addNode(T1_0);
	testCase1.addNode(T1_1);
	testCase1.addNode(T1_2);
	cout << "Intial: " << endl << testCase1.toString();
	Graph reverseTestCase1 = testCase1.invertGraph();
	Node RT1_0(0, { 0, 2 });
	Node RT1_1(1, { 0, 2 });
	Node RT1_2(2, {});
	Graph testCase1Check;
	testCase1Check.addNode(RT1_0);
	testCase1Check.addNode(RT1_1);
	testCase1Check.addNode(RT1_2);
	if (testCase1Check.toString() == reverseTestCase1.toString()) {
		cout << "SUCCESS!" << endl;
		cout << "Reverse TestCase1: " << endl << reverseTestCase1.toString();
	}
	//TEST CASE 2
	cout << "Test Case 2: Topological Ordering" << endl;
	reverseTestCase1.topologicalOrder();
	vector<int> testCase2Check{ 2, 0, 1 };
	if (testCase2Check == reverseTestCase1.getTopologicalOrdering()) {
		cout << "SUCCESS!" << endl;
		cout << reverseTestCase1.printTopologicalOrdering() << endl;
	}
	//TEST CASE 3
	cout << "Test Case 3: Strongly Connected Components" << endl;
	testCase1.processStrongConnections(reverseTestCase1.getTopologicalOrdering());
	vector<set<int>> strongConnectionsTest3{ { 1 },{ 0 },{ 2 } };
	if (strongConnectionsTest3 == testCase1.getStronglyConnectedComponents()) {
		cout << "SUCCESS!" << endl;
		cout << testCase1.printStronglyConnectedComponents();
	}
	//TEST CASE 4 
	cout << "TEST CASE 4: Reverse Graph" << endl;
	Node T4_0(0, { 1, 2 });
	Node T4_1(1, { 0 });
	Node T4_2(2, { 1, 2 });
	Node T4_3(3, {});
	Node T4_4(4, { 3, 4 });
	Graph testCase4;
	testCase4.addNode(T4_0);
	testCase4.addNode(T4_1);
	testCase4.addNode(T4_2);
	testCase4.addNode(T4_3);
	testCase4.addNode(T4_4);
	cout << "Intial: " << endl << testCase4.toString();
	Graph reverseTestCase4 = testCase4.invertGraph();
	Node RT4_0(0, { 1 });
	Node RT4_1(1, { 0, 2});
	Node RT4_2(2, { 0, 2 });
	Node RT4_3(3, { 4 });
	Node RT4_4(4, { 4 });
	Graph testCase4Check;
	testCase4Check.addNode(RT4_0);
	testCase4Check.addNode(RT4_1);
	testCase4Check.addNode(RT4_2);
	testCase4Check.addNode(RT4_3);
	testCase4Check.addNode(RT4_4);
	if (testCase4Check.toString() == reverseTestCase4.toString()) {
		cout << "SUCCESS!" << endl;
		cout << "Reverse TestCase4: " << endl << reverseTestCase4.toString();
	}
	//TEST CASE 5
	cout << "TEST CASE 5: Topological Ordering" << endl;
	reverseTestCase4.topologicalOrder();
	vector<int> topologicalOrderingTest5{ 2, 1, 0, 4, 3 };
	if (topologicalOrderingTest5 == reverseTestCase4.getTopologicalOrdering()) {
		cout << "SUCCESS!" << endl;
		cout << reverseTestCase4.printTopologicalOrdering();
		cout << endl;
	}
	//TEST CASE 6
	cout << "TEST CASE 6: Strongly Connected Components" << endl;
	testCase4.processStrongConnections(reverseTestCase4.getTopologicalOrdering());
	vector<set<int>> strongConnectionsTest6{ { 3 }, { 4 }, { 0, 1, 2 } };
	if (strongConnectionsTest6 == testCase4.getStronglyConnectedComponents()) {
		cout << "SUCCESS!" << endl;
		cout << testCase4.printStronglyConnectedComponents();
	}
	//TEST CASE 7
	cout << "TEST CASE 7:" << endl;
	Node T7_0(0, { 1 });
	Node T7_1(1, { });
	Node T7_2(2, { 3 });
	Node T7_3(3, {});
	Node T7_4(4, { 0, 2, 5 });
	Node T7_5(5, {});
	Graph testCase7;
	testCase7.addNode(T7_0);
	testCase7.addNode(T7_1);
	testCase7.addNode(T7_2);
	testCase7.addNode(T7_3);
	testCase7.addNode(T7_4);
	testCase7.addNode(T7_5);
	cout << "Intial: " << endl << testCase7.toString();
	Graph reverseTestCase7 = testCase7.invertGraph();
	Node RT7_0(0, { 4 });
	Node RT7_1(1, { 0 });
	Node RT7_2(2, { 4 });
	Node RT7_3(3, { 2 });
	Node RT7_4(4, {});
	Node RT7_5(5, { 4 });
	Graph testCase7Check;
	testCase7Check.addNode(RT7_0);
	testCase7Check.addNode(RT7_1);
	testCase7Check.addNode(RT7_2);
	testCase7Check.addNode(RT7_3);
	testCase7Check.addNode(RT7_4);
	testCase7Check.addNode(RT7_5);
	if (testCase7Check.toString() == reverseTestCase7.toString()) {
		cout << "SUCCESS!" << endl;
		cout << "Reverse TestCase7: " << endl << reverseTestCase7.toString();
	}
	//TEST CASE 8
	cout << "TEST CASE 8: Topological Ordering" << endl;
	reverseTestCase7.topologicalOrder();
	vector<int> topologicalOrderingTest7{ 4, 0, 1, 2, 3, 5 };
	if (topologicalOrderingTest7 == reverseTestCase7.getTopologicalOrdering()) {
		cout << "SUCCESS!" << endl;
		cout << reverseTestCase7.printTopologicalOrdering();
		cout << endl;
	}
	//TEST CASE 9
	cout << "TEST CASE 9: Strongly Connected Components" << endl;
	testCase7.processStrongConnections(reverseTestCase7.getTopologicalOrdering());
	vector<set<int>> strongConnectionsTest7{ { 5 },{ 3 },{ 2 },{ 1 },{ 0 },{ 4 } };
	if (strongConnectionsTest7 == testCase7.getStronglyConnectedComponents()) {
		cout << "SUCCESS!" << endl;
		cout << testCase7.printStronglyConnectedComponents();
	}
	//TEST CASE 10
	cout << "TEST CASE 10: All together now!" << endl;
	Node T10_0(0, { 0, 1, 2 });
	Node T10_1(1, {});
	Node T10_2(2, { 3 });
	Node T10_3(3, { 2, 3 });
	Graph testCase10;
	testCase10.addNode(T10_0);
	testCase10.addNode(T10_1);
	testCase10.addNode(T10_2);
	testCase10.addNode(T10_3);
	cout << "Intial: " << endl << testCase10.toString();
	Graph reverseTestCase10 = testCase10.invertGraph();
	Node RT10_0(0, { 0 });
	Node RT10_1(1, { 0 });
	Node RT10_2(2, { 0, 3 });
	Node RT10_3(3, { 2, 3 });
	Graph testCase10Check;
	testCase10Check.addNode(RT10_0);
	testCase10Check.addNode(RT10_1);
	testCase10Check.addNode(RT10_2);
	testCase10Check.addNode(RT10_3);
	if (testCase10Check.toString() == reverseTestCase10.toString()) {
		cout << "SUCCESS!" << endl;
		cout << "Reverse TestCase10: " << endl << reverseTestCase10.toString();
	}
	reverseTestCase10.topologicalOrder();
	vector<int> topologicalOrderingTest10{ 0, 1, 3, 2 };
	if (topologicalOrderingTest10 == reverseTestCase10.getTopologicalOrdering()) {
		cout << "SUCCESS!" << endl;
		cout << reverseTestCase10.printTopologicalOrdering();
		cout << endl;
	}
	testCase10.processStrongConnections(reverseTestCase10.getTopologicalOrdering());
	vector<set<int>> strongConnectionsTest10{ { 2, 3 },{ 1 },{ 0 } };
	if (strongConnectionsTest10 == testCase10.getStronglyConnectedComponents()) {
		cout << "SUCCESS!" << endl;
		cout << testCase10.printStronglyConnectedComponents();
	}
	system("Pause");
	return 0;
}
