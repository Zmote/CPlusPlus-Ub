#include "calc.h"
#include <iostream>
#include <sstream>
#include <string>
#include <limits>

int calc(int const a,int const b,char const op){
	int result;
	switch(op){
		case '+':
			result = (a + b);
			break;
		case '-':
			result = (a - b);
			break;
		case '*':
			result = (a * b);
			break;
		case '/':
			if(b == 0){
				throw std::logic_error("Can't divide through zero\n");
			}else{
				result = a/b;
				break;
			}
		case '%':
			if(b == 0){
				throw std::logic_error("Second argument of modulo can't be zero\n");
			}else{
				result = a%b;
				break;
			}
		default:
			throw std::invalid_argument("No or invalid operator");
	}
	return result;
}

int calc(std::istream& in){
	int a,b;
	char op;
	in >> a;
	in >> op;
	in >> b;
	return calc(a,b,op);
}
