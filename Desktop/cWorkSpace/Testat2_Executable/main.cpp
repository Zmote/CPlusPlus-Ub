#include "word.h"
#include "kwic.h"
#include <iostream>
#include <sstream>
#include <vector>

int main(){
Word myword;
std::vector<Word> words{};
while(std::cin){
	std::cin >> myword;
	words.push_back(myword);
}
for(Word w: words){
	std::cout << w << "\n";
}
//kwic(std::cout,std::cin);

}
