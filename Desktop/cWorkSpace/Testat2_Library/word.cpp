#include "word.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <iterator>
#include <stdexcept>

Word::Word(const std::string c){
	if(!c.empty()){
		for_each(begin(c),end(c),[&](const char i){
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
	using isbuf = std::istreambuf_iterator<char>;
	word.clear();
	isbuf it = find_if(isbuf(in),isbuf(),[](char i){
		return !std::isalpha(i);
	});
	copy_if(isbuf(in),it,begin(word),[&](char i){
		return std::isalpha(i);
	});

//	while(in){
//		if(std::isalpha(in.peek())){
//			word+= in.get();
//		}else{
//			while(!std::isalpha(in.peek()) && !in.eof()){
//				in.get();
//			}
//			if(!word.empty()){
//				break;
//			}
//		}
//	}
}

