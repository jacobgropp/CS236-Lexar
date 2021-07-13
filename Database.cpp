#include "Database.h"

Database::Database() {}

void Database::addRelation(Scheme scheme) {
	Relation newRelation(scheme.getRelationName(), scheme.getHeader());
	relations.insert(pair<string, Relation>(scheme.getRelationName(), newRelation));
}

void Database::addRowToRelation(Fact facts) {
	relations[facts.getFactId()].addRow(facts.getNewRow());
}

void Database::addRowsFromRules(Rule rule) {
	//Evaluate predicates on the right hand side of the rule
	vector<Relation> newQueryRelations;
	for (int i = 0; i < rule.getPredicates().size(); i++) {
		Relation relation = getRelation(rule.getPredicates()[i].getPredicateId());
		Relation resultRelation = relation.execute(rule.getPredicates()[i]);
		newQueryRelations.push_back(resultRelation);
	}
	//Join the relations that result
	Relation resultFromJoin = newQueryRelations[0];
	for (int i = 1; i < newQueryRelations.size(); i++) {
		resultFromJoin = resultFromJoin.naturalJoin(newQueryRelations[i]);
	}
	//Project columns that appear in head predicate
	Relation resultFromProject = resultFromJoin.project(resultFromJoin.findIndeces(rule.getHead()));
//Rename relation to match the schema of the relation in the database
	Relation databaseRelation = getRelation(rule.getHead().getHeadId());
	Relation resultFromRename = resultFromProject.rename(databaseRelation.getHeader());
//Union with the relation in the database
	Relation resultFromUnion = resultFromRename.relationUnion(databaseRelation);
	for (auto row : resultFromUnion.getRows()) {
		relations[rule.getHead().getHeadId()].addRow(row);
	}
}

int Database::getNumberOfFacts() {
	int numberOfFacts = 0;
	map<string, Relation>::iterator it;
	for (it = relations.begin(); it != relations.end(); it++){
		numberOfFacts += it->second.getRows().size();
	}
	return numberOfFacts;
}

Relation Database::getRelation(string name) {
	return relations[name];
}
