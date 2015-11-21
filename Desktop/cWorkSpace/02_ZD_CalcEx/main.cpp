#include "calculator.h"
#include <iostream>

int main(){
	int a{3};
	int b{5};

	calc(a,b,'+');
	calc(a,b,'-');
	calc(a,b,'*');
	calc(5,5,'*');
	calc(a,b,'/');
	calc(26,5,'%');

	try{
		calc(3,0,'/');

	}catch(std::invalid_argument &e){
		std::cerr << e.what();
	}

	try{
		calc(5,0,'%');
	}catch(std::invalid_argument &e){
		std::cerr << e.what();
	}

}
