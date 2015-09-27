#include "calculator.h"
#include <iostream>

int main(){
	int a{3};
	int b{5};

	int resultPlus{calc(a,b,'+')};
	int resultMinus{calc(a,b,'-')};
	int resultDiv{calc(a,b,'/')};
	int resultMulti{calc(a,b,'*')};
	int resultAny{calc(5,5,'*')};
	int resultModulo{calc(26,5,'%')};

	print(std::cout,resultPlus);
	print(std::cout,resultMinus);
	print(std::cout,resultDiv);
	print(std::cout,resultMulti);
	print(std::cout,resultAny);
	print(std::cout,resultModulo);
}
