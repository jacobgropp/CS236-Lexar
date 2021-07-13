#include "Relation.h"
#include <algorithm>

Relation::Relation(string name, Header header) {
	this->name = name;
	this->header = header;
}

Relation::Relation(string name, Header header, set<Row> rows) {
	this->name = name;
	this->header = header;
	this->rows = rows;
}

Relation::~Relation() {}

void Relation::addRow(Row row) {
	rows.insert(row);
	return;
}

Relation Relation::execute(Predicate query) {
	Relation newRelation = Relation(this->name, this->header, this->rows); //creates newRelation to return at the end of method
	vector<Parameter*> newParameters = query.getParameters(); //creates vector of Parameters we will search through to determine methods to call
	bool normalSelect = false;
	vector<int> indeces;
	vector<string> values;
	//SELECT
	for (int i = 0; i < newParameters.size(); i++) {
		if (newParameters[i]->toString().at(0) == '\'') {
			indeces.push_back(i); //This fills up a vector of ints where a string is 
			values.push_back(newParameters[i]->toString()); //This fills up a vector of said strings
			normalSelect = true;
		}
	}
	vector<int> match1;
	vector<int> match2;
	bool matchSelect = false;
	for (int i = 0; i < newParameters.size(); i++) {
		if (newParameters[i]->toString().at(0) != '\'') {
			int tempIterator = i + 1;
			for (int j = tempIterator; j < newParameters.size(); j++) {
				if (newParameters[i]->toString() == newParameters[j]->toString()) {
					match1.push_back(i);
					match2.push_back(j);
					matchSelect = true;
				}
			}
		}
	}
	if (normalSelect) {
		newRelation = newRelation.select(indeces, values);
	}
	if (matchSelect) {
		newRelation = newRelation.select(match1, match2);
	}
	indeces.clear();
	values.clear();
	bool projectAndRename = false;
	//Filling indeces for use with project method
	vector<int> myInts;
	vector<int> finalIndeces;
	//PROJECT and RENAME
	for (int i = 0; i < newParameters.size(); i++) {
		if (newParameters[i]->toString().at(0) != '\'') {
			int index = i;
			for (int j = 0; j < newParameters.size(); j++) {
				if (newParameters[i]->toString() == newParameters[j]->toString()) {
					if (index > j) {
						index = j;
					}
				}
			}
			bool indexSatisfied = true;
			for (int i = 0; i < indeces.size(); i++) {
				if (indeces[i] == index) {
					indexSatisfied = false;
				}
			}
			if (indexSatisfied) {
				indeces.push_back(index);
			}
			bool valueSatisfied = true;
			for (int i = 0; i < values.size(); i++) {
				if (values[i] == newParameters[index]->toString()) {
					valueSatisfied = false;
				}
			}
			if (valueSatisfied) {
				values.push_back(newParameters[index]->toString());
			}

		}
	}
	newRelation = newRelation.project(indeces);
	newRelation = newRelation.rename(values);
	return newRelation;
}

Relation Relation::select(vector<int> indeces, vector<string> values) {
	Relation result = Relation(this->name, this->header);
	for (Row iterator : rows) {
		bool satisfied = true;
		for (int j = 0; j < indeces.size(); j++) {
			if (iterator[indeces[j]] != values[j]) {
				satisfied = false;
			}
		}
		if (satisfied) {
			result.addRow(iterator);
		}
	}
	return result;
}

Relation Relation::select(vector<int> firstMatch, vector<int> secondMatch) {
	Relation result = Relation(this->name, this->header);
	for (Row iterator : rows) {
		bool satisfied = true;
		for (int i = 0; i < firstMatch.size(); i++) {
			if (iterator[firstMatch[i]] != iterator[secondMatch[i]]) {
				satisfied = false;
			}
		}
		if (satisfied) {
			result.addRow(iterator);
		}


	}
	return result;
}

Relation Relation::project(vector<int> indeces) {
	Relation result = Relation(this->name, this->header);
	Header newHeader;
	for (int i = 0; i < indeces.size(); i++) {
		newHeader.push_back(header[indeces[i]]);
	}
	result.header = newHeader;
	for (auto iterator : rows) {
		Row newRow;
		for (int i = 0; i < indeces.size(); i++) {
			newRow.push_back(iterator[indeces[i]]);
		}
		result.addRow(newRow);
	}
	return result;
}


Relation Relation::rename(vector<string> values) {
	Relation result = Relation(this->name, this->header);
	Header newHeader;
	for (int i = 0; i < values.size(); i++) {
		newHeader.push_back(values[i]);
	}
	result.header = newHeader;
	result.rows = rows;
	return result;
}

Relation Relation::naturalJoin(Relation newRelation) {
	//Find the indeces of newRelation's columns that match the current relation
	vector<int> columnsKey = header.mergeColumnsKey(newRelation.getHeader());
	//Create the new Header for the natural join
	Relation result = Relation(this->name, this->header.mergeWith(newRelation.getHeader()));
	if (columnsKey.empty()) {
		for (auto currentRow : rows) {
			for (auto newRelationRow : newRelation.getRows()){
				result.addRow(currentRow.mergeWith(newRelationRow));
			}
		}
	}
	else {
		for (auto currentRow : rows) {
			for (auto newRelationRow : newRelation.getRows()) {
				bool satisfied = true;
				//vector<int> savedIndeces;
				for (int i = 0; i < columnsKey.size(); i++) {
					if (currentRow[columnsKey[i]] != newRelationRow[columnsKey[i + 1]]) {
						satisfied = false;
						break;
					}
					i++;
				}
				if (satisfied) {
					result.addRow(currentRow.mergeWith(newRelationRow, columnsKey));
				}
			}
		}
	}
	return result;
}



Relation Relation::relationUnion(Relation unionRelation) {
	vector<int> newOrderMap = header.createMapFor(unionRelation.getHeader());
	Relation reorderedRelation = Relation(unionRelation.getName(), unionRelation.getHeader().rearrangeHeader(newOrderMap));
	for (auto iterator : unionRelation.getRows()) {
		Row newRow = iterator.rearrangeRow(newOrderMap);
		reorderedRelation.addRow(newRow);
	}
	Relation result = Relation(this->name, this->header);
	if (result.getHeader() == reorderedRelation.getHeader()) {
		//Adding all rows from the current relation
		for (auto iterator : rows) {
			Row newRow;
			for (int i = 0; i < iterator.size(); i++) {
				newRow.push_back(iterator[i]);
			}
			result.addRow(newRow);
		}
		//Adding all rows from the reorderedRelation
		for (auto iterator : reorderedRelation.getRows()) {
			Row newRow;
			for (int i = 0; i < iterator.size(); i++) {
				newRow.push_back(iterator[i]);
			}
			result.addRow(newRow);
		}
	}
	//Return the new relation that has all unique rows from the union of the two relations
	return result;
}

vector<int> Relation::findIndeces(HeadPredicate headPredicate) {
	vector<int> indeces;
	for (int i = 0; i < headPredicate.getParams().size(); i++) {
		for (int j = 0; j < getHeader().size(); j++) {
			if (headPredicate.getParams()[i].toString() == getHeader()[j]) {
				indeces.push_back(j);
				break;
			}
		}
	}
	return indeces;
}

string Relation::getName() {
	return name;
}

Header Relation::getHeader() {
	return header;
}

set<Row> Relation::getRows() {
	return rows;
}

string Relation::toString() {
	stringstream ss;
	for (int i = 0; i < header.size(); i++) {
		ss << header[i] << "  ";
	}
	ss << endl;
	for (auto iterator : rows) {
		for (int j = 0; j < iterator.size(); j++) {
			ss << iterator[j] << "  ";
		}
		ss << endl;
	}
	return ss.str();
}

string Relation::toOutputString() {
	stringstream ss;
	return ss.str();
}