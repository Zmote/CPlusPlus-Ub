#include "algo_head.h"
#include <iostream>
#include <string>
#include <fstream>

int charc(std::istream &in){
	std::string str{};
	std::string strElement{}; // tmp-value, look fo a better solution
	while(in){
		in >> strElement;
		str += strElement;
		if(in.get() == '\n'){
			break;
		}
	}
	return str.length();
}

int allcharc(std::istream &in){
	std::string str;
	std::getline(in,str);
	return str.length();
}

int wc(std::istream &in){
	std::string str;

	while(std::getline(in, str)){
		int counter{};
		for(unsigned int i = 0; i < str.length();i++){
			if(i == 0){
				counter = 1;
			}
			if(str[i] == ' '){
				counter++;
			}
		}
		return counter;
	}
	return 0;
}

int lc(std::istream &in){
	int counter = 0;
	std::cout << "Please enter your filename (with .txt): ";
	std::string line;
	std::string fileName;
	in >> fileName;
	std::ifstream myfile(fileName);
	while (std::getline(myfile, line)){
		if(!line.empty()){
			++counter;
		}
	}
	return counter;
}

//the std::cin.eof() part is there, because I don't want the terminating bit to show on the console.

//#include <algorithm>
//str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());

