#include "kwic.h"
#include "word.h"
#include <iostream>
#include <sstream>
#include <vector>

int main(){

//kwic(std::cout,std::cin);

Word myword{};
std::vector<Word>vec{};
while(std::cin){
	std::cin >> myword;
	std::cout << myword << '\n';
	vec.push_back(myword);
}

std::cout << vec.size();
}
