#include "kwic.h"
#include "word.h"
#include <iterator>
#include <algorithm>
#include <vector>
#include <sstream>
#include <string>

void kwic(std::ostream& out, std::istream& in){
std::vector<std::vector<Word>> sentences{};
std::vector<Word> sentence{};
Word word{};
std::string input{};
while(getline(in,input)){
std::stringstream ss{input};
	while(ss >> word){
		sentence.push_back(word);
	}
	sentences.push_back(sentence);
	sentence.clear();
}

for_each(begin(sentences),end(sentences),[&](std::vector<Word> wordVector){
	std::vector<Word> vec = wordVector;
	for(unsigned int i = 0; i < vec.size();i++){
		std::rotate(begin(vec),begin(vec)+1,end(vec));
		for_each(begin(vec),end(vec),[&](Word i){
			out << i << " ";
		});
		out << '\n';
	}
});

}

