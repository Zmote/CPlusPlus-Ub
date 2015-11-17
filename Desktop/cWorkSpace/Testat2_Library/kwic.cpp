#include "kwic.h"
#include "word.h"
#include <iterator>
#include <algorithm>
#include <vector>
#include <sstream>
#include <string>

void kwic(std::ostream& out, std::istream& in){
std::vector<std::vector<Word>> words{};
std::string word{};
while(getline(in,word)){
	std::stringstream ss{word};
	std::stringstream os{};
	Word myword{};
	ss >> myword;
	os << myword;
	std::vector<Word> sentence{std::istream_iterator<std::string>(os),std::istream_iterator<std::string>()};
	words.push_back(sentence);
}
for_each(begin(words),end(words),[&](std::vector<Word> wordVector){
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

