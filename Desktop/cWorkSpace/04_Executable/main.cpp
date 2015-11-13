#include "w04algo.h"
#include <cmath>
#include <iostream>

int main(){
	//wlist(std::cout,std::cin);
	//printFunctionTable(std::cout,1.0,9.0,4,[](double x){return std::sin(x);});
	//printFunctionTable(std::cout,1.0,9.0,4,[](double x){return x*x;});
	double pi = acos(-1);
	printFunctionTable(std::cout,0,pi,10,[](double x){return std::sin(x);});
	printFunctionTable(std::cout,0,pi,10,[](double x){return std::cos(x);});
	printFunctionTable(std::cout,0,pi,10,[](double x){return std::tan(x);});
}