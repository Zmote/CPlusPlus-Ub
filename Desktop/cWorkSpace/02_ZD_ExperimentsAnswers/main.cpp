#include <iostream>
#include <vector>
#include <iterator>


int main(){
std::string name;
	while(std::cin){
		if(std::cin.peek() == '\n'){
			break;
		}
		name += std::cin.get();
	}
//	std::vector<int> zm{3};
//	std::istream_iterator<char> it;
	std::cout << name;
}


/*int main(){
	int anAnswer{};
	while(std::cin){
		if(!(std::cin >> anAnswer)){
			if(std::cin.eof()){
			std::cout << "EOF called";
		}
			if(std::cin.fail()){
				std::cout << "I failed";
			}
		}else{
			std::cout << anAnswer;;
		}
	}
}*/

/*
 * 1.-----------------------------------------------------------------
 *The streams failbit is set. The char's are still in the stream, but
 *The the stream itself isn't accesible anymore --> you can't keep
 *The reading in new numbers into the stream.
 * */

/*
 *2.------------------------------------------------------------------
 *With a tmp variable, that holds the current info of the stream and
 *adds it to my stream. The std::cin reads up to empty spaces and ignores whitespace,
 *that's why we need to add strings together. You could also use std::cin.get() instead
 *that's of a temp variable and directly += assign it to the string. cin.get() doesn't skip
 *that's whitespace as normal cin does, therefore multiple words can be read in that way. Drawback
 *that's --> the stream doesn't terminate on Enter, we have to listen for \n input and terminate
 *that's ---> "manually"
 * */

/*
 *3.------------------------------------------------------------------
 *Because else it would manipulate only the passed variables within the function
 *of getline and we'd have no side-effects on our original strings
 * */

