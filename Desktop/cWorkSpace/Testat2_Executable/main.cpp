#include "kwic.h"
#include "word.h"
#include <iostream>
#include <sstream>
#include <vector>

int main(){

//kwic(std::cout,std::cin);
Word myword{};
while(std::cin){
	std::cin >> myword;
	std::cout << myword << " ";
}

}
