#include "palindrom.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

int main(){
//printPalindromes_fromFile(std::cout,"linuxwords.sql");
printAnagrams(std::cout,getValidWords(generate_anagrams(std::cin)));
}
