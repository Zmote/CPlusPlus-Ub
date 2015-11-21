#include "calculator.h"
#include <iostream>

int calc(int a,int b,char op){
	switch(op){
		case '+': return (a + b);break;
		case '-': return (a - b);break;
		case '/': return (a/b);break;
		case '*': return (a*b);break;
		case '%': return (a%b);break;
		default: return 0;
	}
}

void print(std::ostream& out, int number){
	out << "Result: " << number << "\n";
}
