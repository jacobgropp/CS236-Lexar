#pragma once
#include <vector>
#include <string>

using namespace std;

class Row : public vector<string> {
public:
	Row rearrangeRow(vector<int> newOrderingMap);

	Row mergeWith(Row row, vector<int> index);
	Row mergeWith(Row row);
};
