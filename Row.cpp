#include "Row.h"

#include <iostream>
using namespace std;

Row Row::rearrangeRow(vector<int> newOrderingMap) {
	Row newRow;
	for (int i = 0; i < newOrderingMap.size(); i++) {
		newRow.push_back(this->at(newOrderingMap[i]));
	}
	return newRow;
}

Row Row::mergeWith(Row row, vector<int> indeces) {
	Row newRow;
	for (int i = 0; i < size(); i++) {
		newRow.push_back(this->at(i));
	}
	for (int i = 0; i < row.size(); i++) {
		bool satisfied = true;
		for (int j = 1; j < indeces.size(); j++) {
			if (i == indeces[j]) satisfied = false;
			j++;
		}
		if(satisfied) {
			newRow.push_back(row[i]);
		}
	}
	return newRow;
}

Row Row::mergeWith(Row row) {
	Row newRow;
	for (int i = 0; i < size(); i++) {
		newRow.push_back(this->at(i));
	}
	for (int i = 0; i < row.size(); i++) {
		newRow.push_back(row[i]);
	}
	return newRow;
}