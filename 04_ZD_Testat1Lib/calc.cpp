#include "calc.h"
#include <iostream>
#include <sstream>
#include <string>

int calc(int a,int b,char op){
	int result;
	switch(op){
		case '+': result = (a + b);break;
		case '-': result = (a - b);break;
		case '/':
			if(b == 0){
				throw std::invalid_argument("Can't divide through zero\n");
			}else{
				result = a/b;
			}
			break;
		case '*': result = (a*b);break;
		case '%':
			if(b == 0){
				throw std::invalid_argument("Second argument of modulo can't be zero\n");
			}else{
				result = a%b;
			}
		default: throw std::invalid_argument("No or invalid operator");
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

void print(std::ostream& out, int a, int b, char op, int number){
	out << "Result: "<< a << " " << op  << " " << b << " = "<< number << "\n";
}
