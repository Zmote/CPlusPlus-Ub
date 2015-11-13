#include "word.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <string>
//TODO: Constructor: Can it have a default value?
//TODO: Write Tests
//TODO: Ob neue W�rter erzeugt werden --> check was genau gemeint ist damit?

Word::Word(std::string c){
	if(!c.empty()){
		for_each(begin(c),end(c),[&](char i){
			if(!std::isalpha(i) || std::isspace(i)){
				throw std::invalid_argument("Invalid characters detected");
			}else{
				word = c;
			}
		});
	}else{
		throw std::invalid_argument("Word can't be empty!");
	}
};

void Word::print(std::ostream& o){
	o << word;
}

std::string Word::toLower() const{
	std::string lowerString{};
	for_each(begin(word),end(word),[&](auto i){
		lowerString += std::tolower(i);
	});
	return lowerString;
}

std::vector<std::string> separateWords(std::string& input, std::string& word){
	std::vector<std::string> vec;
	for_each(begin(input),end(input),[&](char i){
			if(std::isalpha(i) && !std::isspace(i)){
				word += i;
			}else{
				if(!word.empty()){
					vec.push_back(word);
					word.clear();
				}
			}
		});
		vec.push_back(word);
		word.clear();
		return vec;
}

void Word::read(std::istream& i){
	using in = std::istreambuf_iterator<char>;
	word.clear();
	std::vector<std::string> vec;
	std::string inputString{in(i),in()};
	vec = separateWords(inputString,word);
	for_each(begin(vec),end(vec),[&](auto i){
		word += (i+" "); //space only tmp, for visibility?!
	});
	while(word.back() == ' '){
		word.pop_back();
	}
}

