#include "hello_c.h"
#include <ostream>
#include <iostream>

Hello::Hello(std::string str) {
	memberString = str;
}

void Hello::sayHello(std::ostream &o) const {
	o << memberString;
}

void Hello::sayHello(std::string &str) const {
	std::cout << str;
}
