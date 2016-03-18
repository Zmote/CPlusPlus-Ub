#include "large_nums.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>

int charc(std::istream &in){
	std::string str{(std::istream_iterator<char>(in)),(std::istream_iterator<char>())};
	std::string out{};
	for_each(begin(str),end(str),[&](auto i){out += i;});
	return out.length();
}

int allac(std::istream &in){
	std::string str{(std::istreambuf_iterator<char>(in)),(std::istreambuf_iterator<char>())};
	int aTotal{0};
	for_each(begin(str),end(str),[&](auto i){
		if(i == 'a'){
			aTotal++;
		}
	});
	return aTotal;
}

int allcharc(std::istream &in){
	std::string str{(std::istreambuf_iterator<char>(in)),(std::istreambuf_iterator<char>())};
	std::string out{};
	for_each(begin(str),end(str),[&](auto i){out += i;});
	return out.length();
}

int wc(std::istream &in){
	std::string inStr;
	getline(in,inStr);
	std::stringstream stream{inStr};
	return std::distance(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>());
}

int lc(std::istream &in){
	int counter{1};
	std::string fileName;
	in >> fileName;
	std::ifstream myfile(fileName);
	std::string str((std::istreambuf_iterator<char>(myfile)),
		                 std::istreambuf_iterator<char>());
	for_each(begin(str),end(str),[&](auto i){
		if(i == '\n'){
			++counter;
		}
	});
	return str.empty()? 0:counter;
}
