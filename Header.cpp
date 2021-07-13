#include "Header.h"
#include <algorithm>

//UNION Methods
vector<int> Header::createMapFor(Header header) {
	vector<int> result;
	for (int i = 0; i < header.size(); i++) {
		for (int j = 0; j < this->size(); j++) {
			if (header[i] == this->at(j)) {
				result.push_back(j);
			}
		}
	}
	return result;
}

Header Header::rearrangeHeader(vector<int> newOrderingMap) {
	Header newHeader;
	for (int i = 0; i < newOrderingMap.size(); i++) {
		newHeader.push_back(this->at(newOrderingMap[i]));
	}
	return newHeader;
}

//NATURALJOIN Methods
vector<int> Header::mergeColumnsKey(Header header) {
	vector<int> result;
	for (int i = 0; i < size(); i++) {
		for (int j = 0; j < header.size(); j++) {
			if (this->at(i) == header[j]) {
				result.push_back(i);
				result.push_back(j);
			}
		}
	}
	return result;
}

Header Header::mergeWith(Header header) {
	for (int i = 0; i < header.size(); i++) {
		bool addVariable = true;
		for (int j = 0; j < this->size(); j++) {
			if (header[i] == this->at(j)) addVariable = false;
		}
		if(addVariable) push_back(header[i]);
	}
	//sort(begin(), end());
	//erase(unique(begin(), end()), end());
	return *this;
}

