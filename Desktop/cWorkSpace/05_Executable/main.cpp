#include "calc.h"
#include "sevensegment.h"
#include "pocketcalculator.h"
#include <iostream>

int main(){
	while(std::cin){
		Pocketcalculator::calculate(std::cout,std::cin);
	}
}
