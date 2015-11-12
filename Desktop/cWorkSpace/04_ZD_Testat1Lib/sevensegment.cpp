#include "large_nums.h"
#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>

std::vector<std::vector<std::string>> numbers {
	{
		" _ ",
		"| |",
		"|_|"
	},
	{
		"   ",
		"  |",
		"  |",
	},
	{
		" _ ",
		" _|",
		"|_ ",
	},
	{
		" _ ",
		" _|",
		" _|",
	},
	{
		"   ",
		"|_|",
		"  |",
	},
	{
		" _ ",
		"|_ ",
		" _|",
	},
	{
		" _ ",
		"|_ ",
		"|_|",
	},
	{
		" _ ",
		"  |",
		"  |",
	},
	{
		" _ ",
		"|_|",
		"|_|",
	},
	{
		" _ ",
		"|_|",
		" _|",
	}
};

void printLargeNumber(std::ostream &o,std::istream &in){
	std::string givenNumber{};
	getline(in,givenNumber);
	int x;
	for(unsigned int i = 0; i < 3;i++){
		for(unsigned int j = 0; j < givenNumber.size();j++){
			x = (int)givenNumber.at(j) - 48;
			o << numbers.at(x).at(i);
		}
		o << '\n';
	}
}

void printLargeNumber(std::ostream &o, int in){
	std::ostringstream ostr{};
	ostr << in;
	std::string givenNumber{ostr.str()};
	for(int i = 0; i < 3; i++){
		for_each(begin(givenNumber),end(givenNumber),[&](auto j){
			int x = (int)j - 48;
			o << numbers.at(x).at(i);
		});
		o << '\n';
	}

}

void printSingleLNumber(std::ostream &o, int in){
	for_each(begin(numbers.at(in)),end(numbers.at(in)),[&](auto i){
		o << i << '\n';
	});
}
