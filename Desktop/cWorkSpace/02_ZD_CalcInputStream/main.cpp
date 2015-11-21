#include "calculator.h"
#include <iostream>

int main(){
	while(std::cin){
		try{
			std::cout << "= " << calc(std::cin) << "\n";
		}catch(std::invalid_argument& e){
			std::cerr << e.what();
		}
	}
}
