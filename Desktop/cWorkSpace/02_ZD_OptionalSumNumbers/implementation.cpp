#include "sumi.h"
#include <iostream>

void sumi(std::istream &in){
	int sum{0};
	int num;
	//std::cout << "Enter your numbers(ex. 3 4 5): \n";
	while(in >> num){
		if(in.peek() == '\n'){
			sum += num;
			break;
		}
		sum += num;
	}
	std::cout << sum << '\n';
}
//changing int's to float was sufficient
void sumf(std::istream &in){
	float sum{0};
	float num;
	std::cout << "Enter your numbers(ex. 3.14 4.5 5.1): \n";
	while(in >> num){
		if(in.peek() == '\n'){
			sum += num;
			break;
		}
		sum += num;
	}
	std::cout << sum << '\n';
}

void averagei(std::istream &in){
	int sum{0};
	int num;
	int counter{0};

	std::cout << "Enter your numbers(ex. 3 4 5): \n";

	while(in >> num){
		if(!in.fail()){
			++counter;
			in.clear();
		}
		if(in.peek() == '\n'){
			sum += num;
			break;
		}
		sum += num;
	}

	int average = sum/counter;
	std::cout << "The average is: " << average << '\n';
}

void averagef(std::istream &in){
	float sum{0};
	float num;
	int counter{0};

	std::cout << "Enter your numbers(ex. 3 4 5): \n";

	while(in >> num){
		if(!in.fail()){
			++counter;
			in.clear();
		}
		if(in.peek() == '\n'){
			sum += num;
			break;
		}
		sum += num;
	}
	if(in.eof()){return;}
	float average = sum/counter;
	std::cout << "The average is: " << average << '\n';
}
