#include "large_nums.h"
#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>

const std::vector<std::vector<std::string>> numbers {
	{
		" - ",
		"| |",
		"   ",
		"| |",
		" - "
	},
	{
		"   ",
		"  |",
		"   ",
		"  |",
		"   ",
	},
	{
		" - ",
		"  |",
		" - ",
		"|  ",
		" - ",
	},
	{
		" - ",
		"  |",
		" - ",
		"  |",
		" - ",
	},
	{
		"   ",
		"| |",
		" - ",
		"  |",
		"   ",
	},
	{
		" - ",
		"|  ",
		" - ",
		"  |",
		" - ",
	},
	{
		" - ",
		"|  ",
		" - ",
		"| |",
		" - ",
	},
	{
		" - ",
		"  |",
		"   ",
		"  |",
		"   ",
	},
	{
		" - ",
		"| |",
		" - ",
		"| |",
		" - ",
	},
	{
		" - ",
		"| |",
		" - ",
		"  |",
		" - ",
	}
};

void drawLine(int i, std::string givenNumber, int scale, std::ostream & o){
	for_each(begin(givenNumber),end(givenNumber),[&](auto j){
		int x = (int)j - 48;
		std::string lineBuilder{};
		std::string middleElement{};
		lineBuilder = numbers.at(x).at(i);
		middleElement = numbers.at(x).at(i).at(1);
		for(int k = 0; k < scale; k++){
			lineBuilder.insert(1,middleElement);
		}
		o << lineBuilder;
	});
	o << '\n';
}

void printLargeNumber(std::ostream &o,std::istream &in){
	std::string givenNumber{};
	getline(in,givenNumber);
	int x;
	for(unsigned int i = 0; i < 5;i++){
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
	for(int i = 0; i < 5; i++){
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

void printLargeNumber(std::ostream &o, std::istream &in, int scale){
	std::string givenNumber{};
	getline(in,givenNumber);
	for(int i = 0; i < 5; i++){
		if(i == 0 || i == 2 || i == 4){
			drawLine(i, givenNumber, scale, o);
		}
		if(i == 1 || i == 3){
			for(int z = 0; z < scale;z++){
				drawLine(i, givenNumber, scale, o);
			}
		}
	}
}
