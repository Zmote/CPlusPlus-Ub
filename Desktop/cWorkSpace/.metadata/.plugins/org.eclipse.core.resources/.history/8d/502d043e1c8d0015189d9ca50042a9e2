#include "anagrams.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include <fstream>
#include <iterator>

std::set<std::string> words() {
	std::set<std::string> wordList { };
	std::string line { };
	std::ifstream myfile("/usr/share/dict/words");
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			wordList.insert(line);
		}
	}
	return wordList;
}

void anagrams(std::ostream &out, std::string s) {
	auto const wordList = words();
	std::set<std::string> anagramList { };
	sort(s.begin(), s.end());
	do {
		if (wordList.count(s) > 0) {
			anagramList.insert(s);
		}
	} while (std::next_permutation(s.begin(), s.end()));
	std::copy(anagramList.begin(), anagramList.end(), std::ostream_iterator<std::string> (out, "\n"));
	out << "Permutations: " << anagramList.size() << "\n";
}


