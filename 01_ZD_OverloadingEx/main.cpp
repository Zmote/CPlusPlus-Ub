#include "hello_c.h"
#include <iostream>

int main() {
	Hello hello{ "Zafer is the best\n" };
	hello.sayHello(std::cout);

	std::string mystring = "Hello World!";
	hello.sayHello(mystring);
}
