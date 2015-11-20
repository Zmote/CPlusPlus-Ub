#include "word.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <locale>
#include <string>
//TODO: Constructor: Can it have a default value?
//TODO: Write Tests
//TODO: Ob neue W�rter erzeugt werden --> check was genau gemeint ist damit?

Word::Word(const std::string c){
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

std::vector<std::string> separateWords(const std::string& input, std::string& word){
	std::vector<std::string> vec;
//	for_each(begin(input),end(input),[&](char i){
//			if(std::isalpha(i) && !std::isspace(i)){
//				word += i;
//			}else{
//				if(!word.empty()){
//					vec.push_back(word);
//					word.clear();
//				}
//			}
//		});
//		vec.push_back(word);
//		word.clear();
		return vec;
}

void Word::read(std::istream& in){
	//TODO: Optimize, less loops?try with istreambuf_iterators
	word.clear();
	while(in){
		if(std::isalpha(in.peek())){
			word+= in.get();
		}else{
			while(in){
				if(!std::isalpha(in.peek())){
					in.get();
				}else{
					break;
				}
			}
			break;
		}
	}
}

