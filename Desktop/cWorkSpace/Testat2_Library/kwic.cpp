#include "kwic.h"
#include "word.h"
#include <algorithm>
#include <vector>
#include <sstream>
#include <set>
#include <string>

void printSet(std::ostream& out, std::set<std::vector<Word>>& setOfSentencesWithRotations){
	for_each(begin(setOfSentencesWithRotations),end(setOfSentencesWithRotations),[&](std::vector<Word> sentence){
		for(Word word:sentence){
			out << word << " ";
		}
		out << "\n";
	});
}

std::set<std::vector<Word>> buildSetWithRotations(std::vector<std::vector<Word>>& sentences){
std::set<std::vector<Word>> setOfSentences{};
for_each(begin(sentences),end(sentences),[&](std::vector<Word> wordVector){
	std::vector<Word> vec = wordVector;
	setOfSentences.insert(vec);
	for(unsigned int i = 0; i < vec.size();i++){
		std::rotate(begin(vec),begin(vec)+1,end(vec));
		setOfSentences.insert(vec);
	}
});
return setOfSentences;
}

std::vector<std::vector<Word>> buildLinesFromInput(std::istream& in){
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
	return sentences;
}

void kwic(std::ostream& out, std::istream& in){
std::vector<std::vector<Word>> sentences = buildLinesFromInput(in);
std::set<std::vector<Word>> setOfSentencesWithRotations = buildSetWithRotations(sentences);
printSet(out,setOfSentencesWithRotations);
}

