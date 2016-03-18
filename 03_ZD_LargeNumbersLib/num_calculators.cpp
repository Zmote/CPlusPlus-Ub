#include "large_nums.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

void multab(std::ostream &o,std::istream &in){
	int upperLevel{};
	in >> upperLevel;
	std::vector<int> vec(upperLevel);
	iota(begin(vec),end(vec),1);
	for_each(begin(vec),end(vec),[&](auto it){
		for_each(begin(vec),end(vec),[&](auto i){
			std::cout << std::left << it << std::setw(2)<< " x " << std::setw(2) << i
					<< std::setw(2)<< " = " << std::setw(2)<< i*it<< '\n';
		});
		std::cout << '\n';
	});

}

void fractab(std::ostream &o,std::istream &in){
	double upperLevel{};
	in >> upperLevel;
	std::vector<double> vec(upperLevel);
	iota(begin(vec),end(vec),1);
	for_each(begin(vec),end(vec),[&](auto it){
		for_each(begin(vec),end(vec),[&](auto i){
			o << std::left << it << std::setw(2)<< " / " << std::setw(2) << i
					<< std::setw(2)<< " = " << std::setw(2) << std::setprecision(4)<< it/i<< '\n';
		});
		o << '\n';
	});

}

void sumi(std::ostream &o,std::istream &in){
std::vector <int> vec;
int myInt;
while(in){
	if(in.peek() == '\n'){
		break;
	}
	in >> myInt;
	vec.push_back(myInt);
}
o << "The sum is: "<< accumulate(begin(vec),end(vec),0);
}

void sumd(std::ostream &o,std::istream &in){
	std::vector <double> vec;
	double myDouble;
	while(in){
		if(in.peek() == '\n'){
			break;
		}
		in >> myDouble;
		vec.push_back(myDouble);
	}
	o << "The sum is: "<< accumulate(begin(vec),end(vec),0.0);
}
