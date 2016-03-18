#include <iostream>
#include "sayHello.h"
using namespace std;

void sayHello(std::ostream &out){
	cout << "!!!Hello World!!!\n";
}

void sayHello(std::string str){
	cout << str;
}
