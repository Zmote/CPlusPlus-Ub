#include "palindrom.h"
#include "word.h"
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <set>
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

void printAnagrams(std::ostream& out, std::set<std::string> myset){
	std::ostream_iterator<std::string> out_it{out, "\n"};
	copy(begin(myset),end(myset),out_it);
}

std::set<std::string> generate_anagrams(std::istream& in){
	std::string input{};
	getline(in,input);
	std::set<std::string> wpalindromes{};

	//for no lowercase/uppercase distinguishment of words
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);

	//generate all permutations of a word or input
	do{
		std::stringstream ss{input};
		wpalindromes.insert(std::istream_iterator<std::string>(ss),std::istream_iterator<std::string>());
		//wpalindromes.insert(input);
	}while(std::next_permutation(input.begin(),input.end()));

	//separate words from generated permutations
	//TODO: --> currently, your algorithm sepearates vacation and time and generates
	//permutations separately for each word, but it should generate permutations
	//from both words and then separated them into words --> UPDATE:
	//This algorithm seems right, but takes forever --> find fix
	return wpalindromes;
}


std::set<std::string> getValidWords(std::set<std::string> permutations){
	std::string line{};
	std::set<std::string> validWords{};
	std::fstream myfile ("linuxwords.sql");
	if (myfile.is_open())
		{
			while(getline(myfile,line))
			{
				//for no lowercase/uppercase distinguishment of words --> find optimized version
				std::transform(line.begin(),line.begin()++,line.begin(),std::tolower);
				std::cout << line << '\n';
			 for_each(begin(permutations),end(permutations),[&](std::string i){
					 if(i == line){
						 validWords.insert(i);
					 }
			 });
			}
		}
	myfile.close();
	return validWords;
}






















