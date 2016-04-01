#include <iostream>
#include <vector>
#include <cctype>
#include <string>
#include <algorithm>

	std::vector<char> alphabet{};

void constructAlphabet(){
	int start{(int)'A'};
	int end{(int)'Z'};
	int range = {end - start};

	for(int i = 0;i <= range;i++){
		alphabet.push_back(start++);
	}
}

int findAlphabetPos(char i){
	for(unsigned int j = 0;j < alphabet.size()-1;j++){
		if(i == alphabet.at(j)){
			return j;
		}
	}
	return -1;
}

int main(){
	constructAlphabet();
// BTEZ FSIJWJ MZSIJWY OFMWJ GWFZHMYJS, GWFZHMJS XNJ KZJSK RNSZYJS.
	std::vector<char> input_sentence{};
	std::vector<char> output_sentence{};
	char startCharacter{'A'};
	char targetCharacter{'V'};
	int keyStep{(int)targetCharacter - (int)startCharacter};

	while(std::cin){
		if(std::cin.peek() == '\n'){
			break;
		}
		input_sentence.push_back(std::cin.get());
	}

	for(unsigned int i = 0; i < input_sentence.size();i++){
		input_sentence[i] = std::toupper(input_sentence[i]);
	}

	for(char i:input_sentence){
		if(std::isalpha(i)){
			int pos = findAlphabetPos(i);
			pos = pos + keyStep;
			int newPos = pos%alphabet.size();
			char newChar = alphabet.at(newPos);
			output_sentence.push_back(newChar);
		}else{
			output_sentence.push_back(i);
		}
	}

	for(char i:output_sentence){
		std::cout << i;
	}

}
