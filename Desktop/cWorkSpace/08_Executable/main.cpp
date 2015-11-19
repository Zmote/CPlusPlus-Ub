#include "palindrom.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <unordered_set>
#include <algorithm>

int main(){
//printPalindromes_fromFile(std::cout,"linuxwords.sql");
//printAnagrams(std::cout,getValidWords(generate_anagrams(std::cin)));
//printAnagrams(std::cout,findAnagrams(std::cin));
//
//time measured: 259 ms, 270ms, 278ms
//std::istringstream ss{"I am hulk"};
//unsigned int start = clock();
//std::unordered_set<std::string> myset = findAnagrams(ss);
//std::cout << "Time in miliseconds: " << clock()-start << " ms\n";
//printAnagrams(std::cout,myset);
//
//time measured: 201 ms, 185ms, 178ms, 192ms, 181ms
//std::istringstream ss{"I am hulk"};
//unsigned int start = clock();
//std::unordered_set<std::string> myset = getValidWords(generate_anagrams(ss));
//std::cout << "Time in miliseconds: " << clock()-start << " ms\n";
//printAnagrams(std::cout,myset);
//
//time measured:170ms,164ms, 162ms
//std::istringstream ss{"I am hulk"};
//unsigned int start = clock();
//std::unordered_set<std::string> myset = generate_anagrams(ss);
//std::cout << "Time in miliseconds: " << clock()-start << " ms\n";
//
//time measured:17ms,14ms,19ms
//std::istringstream ss{"I am hulk"};
//std::unordered_set<std::string> anagrams = generate_anagrams(ss);
//unsigned int start = clock();
//std::unordered_set<std::string> myset = getValidWords(anagrams);
//std::cout << "Time in miliseconds: " << clock()-start << " ms\n";
//
//time measured:~101,757 seconds, about 2 minutes
//std::istringstream ss{"Vacation time"};
//unsigned int start = clock();
//std::unordered_set<std::string> myset = getValidWords(generate_anagrams(ss));
//std::cout << "Time in miliseconds: " << clock()-start << " ms\n";
//printAnagrams(std::cout,myset);
//
//Can't find active in list of permutations, why?
//std::stringstream ss{"Vacation time"};
//std::unordered_set<std::string> myset = generate_anagrams(ss);
//if(myset.find("active") != myset.end()){
//	std::cout << "Found 'active'!";
//}

printAnagrams(std::cout,getValidWords(generate_anagrams(std::cin)));

}
