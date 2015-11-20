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
//TODO: Ob neue Wörter erzeugt werden --> check was genau gemeint ist damit?

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
			while(in){
				if(!std::isalpha(in.peek()) && !in.eof()){
					in.get();
				}else{
					break;
				}
			}
			break;
		}
	}
}

