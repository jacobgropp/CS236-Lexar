#pragma once
#include <vector>
#include <string>

using namespace std;

class Header : public vector<string> {
public:
	vector<int> createMapFor(Header header);
	Header rearrangeHeader(vector<int> newOrderingMap);

	vector<int> mergeColumnsKey(Header header);
	Header mergeWith(Header header);
};
