#include "palindrom.h"
#include "word.h"
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <fstream>
#include <set>
#include <unordered_set>
#include <iterator>

bool is_palindrom(std::string input){
	if(input.empty()){
		//empty word is a palindrom of some sorts, right?
		return true;
	}
	std::string container{input};
	for(char i:input){
		if(std::tolower(i) != std::tolower(container.back())){
			return false;
		}
		container.pop_back();
	}
	return true;
}

void printPalindrome(std::ostream& out, std::string input){
	if(is_palindrom(input)){
		out << input + "\n";
	}
}


void printPalindromes_fromFile(std::ostream& out, std::string url){
	std::string line;
	std::fstream myfile (url);
	if (myfile.is_open())
	{
		while(getline(myfile,line))
		{
		 printPalindrome(out, line);
		}
	}
	myfile.close();
}

void printAnagrams(std::ostream& out, std::unordered_set<std::string> myset){
	std::ostream_iterator<std::string> out_it{out, "\n"};
	std::set<std::string> mySortedSet{begin(myset),end(myset)};
	copy(begin(mySortedSet),end(mySortedSet),out_it);
}

std::unordered_set<std::string> generate_anagrams(std::istream& in){
	std::string input{};
	getline(in,input);
	std::unordered_set<std::string> wpalindromes{};

	//for no lowercase/uppercase distinguishment of words
	std::transform(input.begin(), input.begin() + 1, input.begin(), ::tolower);

	//generate all permutations of a word or input
	do{
		std::stringstream ss{input};
		wpalindromes.insert(std::istream_iterator<std::string>(ss),std::istream_iterator<std::string>());
	}while(std::next_permutation(input.begin(),input.end()));
	return wpalindromes;
}

std::unordered_set<std::string> getValidWords(std::unordered_set<std::string> permutations){
	std::string line{};
	std::unordered_set<std::string> validWords{};
	std::fstream myfile ("linuxwords.sql");
	if (myfile.is_open()){
			while(getline(myfile,line))
			{
			//for no lowercase/uppercase distinguishment of words --> find optimized version
			std::transform(line.begin(),line.begin() + 1,begin(line),::tolower);
			if(permutations.find(line) != permutations.end()){
				validWords.insert(line);
			}
			}
		}
	myfile.close();
	return validWords;
}





















