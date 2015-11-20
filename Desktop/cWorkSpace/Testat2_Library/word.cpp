#include "word.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>

//TODO: Write Tests
//TODO: Optimize algorithms
//TODO: check includes
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

void Word::read(std::istream& in){
	word.clear();
	while(in){
		if(std::isalpha(in.peek())){
			word+= in.get();
		}else{
			while(!std::isalpha(in.peek()) && !in.eof()){
				in.get();
			}
			break;
		}
	}
	//TODO: Find a way to avoid word creation on flush
	Word newWord{word};
	*this = newWord;
}

