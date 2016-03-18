#include "overload.h"
#include <iostream>

namespace overload{
	namespace awesome{
	void incr(int& var, unsigned delta) {
		var += delta;
		std::cout << var;
	}
	void incr(int& var) {
			++var;
			std::cout << "overload scope: " <<var;
		}
	}
}

void incr(int& var) {
		++var;
		std::cout << "global scope: " << var;
}

int main(){
	using overload::awesome::incr;
	int i{3};
	incr(i); //overload scope
}
