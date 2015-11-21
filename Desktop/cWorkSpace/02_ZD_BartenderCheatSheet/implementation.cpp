#include "cheatsheat.h"
#include <iostream>
#include <iomanip>
#include <string>

void calculateTable(std::string drink, std::string drinkType, double price){
	for(int i = 1; i <= 10;i++){
		std::cout << std::left << std::setw(10) << std::setprecision(6)
		<< "|" << i <<  "x\t \'" << drinkType << "\' " << drink << " = " <<  '\t'
				<< (i*price) << ".-\t CHF \t |"<< '\n';
	}
	std::cout << '\n';
}

void calculateTable(std::string drink, double price){
	for(int i = 1; i <= 10;i++){
		std::cout << std::left << std::setw(10) << std::setprecision(6)
		<< "|" << i <<  "x\t" << drink << " = " <<  '\t'
				<< (i*price) << ".-\t CHF \t |"<< '\n';
	}
	std::cout << '\n';
}
