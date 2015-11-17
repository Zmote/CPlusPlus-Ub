#include "w09_algo.h"
#include "word.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <set>
#include <map>

std::vector<Word> buildVector(std::istream& in){
using it = std::istream_iterator<std::string>;
Word myword{};
std::stringstream ss{};
in >> myword;
ss << myword;
std::vector<Word> vec{it(ss),it()};
return vec;
}

void prepareContainers(std::vector<Word>& vec,std::set<Word>& set,
		std::multiset<Word>& multiset, std::multimap<const int, Word>& map){
for_each(begin(vec),end(vec),[&](Word word){
	set.insert(word);
	multiset.insert(word);
});

for_each(begin(set),end(set),[&](Word word){
	map.insert({multiset.count(word),word});
});
}

int wcount(std::istream& in){
std::vector<Word> vec = buildVector(in);
return vec.size();
}

int wdiffcount(std::istream& in){
std::vector<Word> vec = buildVector(in);
std::set<Word> set;
for_each(begin(vec),end(vec),[&](Word word){
	set.insert(word);
});
return set.size();
}

void wfavorite(std::ostream& out, std::istream& in){
std::vector<Word> vec = buildVector(in);
std::set<Word> set{};
std::multiset<Word> multiset{};
std::multimap<const int,Word> map{};

prepareContainers(vec,set,multiset,map);

int limit = 20;
for_each(rbegin(map),rend(map),[&](std::pair<const int,Word> p){
	if(limit >= 0){
	Word myword = p.second;
	out <<  myword << ":" << p.first << "\n";
	limit--;
	}else{
		return;
	}
});
}

void wordle(std::ostream& out, std::istream& in){
//TODO: wfavorite, but ignoring german.stop/english.stop words.
}

















