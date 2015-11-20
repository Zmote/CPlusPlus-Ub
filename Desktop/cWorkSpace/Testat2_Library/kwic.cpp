#include "kwic.h"
#include "word.h"
#include <iterator>
#include <algorithm>
#include <vector>
#include <sstream>
#include <set>
#include <string>

void kwic(std::ostream& out, std::istream& in){
std::vector<std::vector<Word>> sentences{};
std::vector<Word> sentence{};
Word word{};
std::string input{};
while(getline(in,input)){
std::stringstream ss{input};
	while(ss){
		ss >> word;
		sentence.push_back(word);
	}
	sentences.push_back(sentence);
	sentence.clear();
}
//TODO: Helper functions
//TODO: Code Optimizations
std::set<std::vector<Word>> setOfSentences;
for_each(begin(sentences),end(sentences),[&](std::vector<Word> wordVector){
	std::vector<Word> vec = wordVector;
	setOfSentences.insert(vec);
	for(unsigned int i = 0; i < vec.size();i++){
		std::rotate(begin(vec),begin(vec)+1,end(vec));
		setOfSentences.insert(vec);
	}
});

for_each(begin(setOfSentences),end(setOfSentences),[&](std::vector<Word> sentence){
	for(Word word:sentence){
		out << word << " ";
	}
	out << "\n";
});

}

