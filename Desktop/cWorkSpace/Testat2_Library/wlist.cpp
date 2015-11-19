#include "wlist.h"
#include "word.h"
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <set>

void wlist(std::ostream &out, std::istream &in){
	using namespace std;
	Word myword{};
	in >> myword;
	stringstream ss{};
	ss << myword;
	vector<Word> vec{istream_iterator<string>(ss),istream_iterator<string>()};
	set<Word> mySet{begin(vec),end(vec)};
	for_each(begin(mySet),end(mySet),[&](auto i){
		out << i << '\n';
	});
}