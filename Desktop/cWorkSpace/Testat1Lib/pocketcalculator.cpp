#include "calc.h"
#include "sevensegment.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

bool checkInput(std::string &str, unsigned int screenDigitLimit){
	int NaNCounter{0};
	std::string operandLength{};
	bool invalidOperand = false;
	for_each(begin(str),end(str),[&](auto i){
		if(i < '0' || i > '9'){
			NaNCounter++;
			if(operandLength.length() > screenDigitLimit){
				invalidOperand = true;
			}
			operandLength.clear();
		}
		operandLength += i;
	});
	return invalidOperand || NaNCounter > 1;
}

std::string buildOutput(std::istringstream &inputStream, unsigned int screenDigitLimit){
	std::string str{(std::istreambuf_iterator<char>(inputStream)),
		(std::istreambuf_iterator<char>())};
	int errValue = INT_MAX;
	int result;
	if(checkInput(str,screenDigitLimit)){
		result = errValue;
	}else{
		std::istringstream inStream{str};
		try{
			result = calc(inStream);
		}catch(std::exception &e){
			result = errValue;
		}
	}
	std::string resultString = std::to_string(result);
	if(result == errValue || resultString.size() > screenDigitLimit){
		resultString = "error";
	}
	screenDigitLimit -= resultString.size();
	for(unsigned int i = 0;i < screenDigitLimit;i++){
		resultString.insert(0," ");
	}
	return resultString;
}

void calculate(std::ostream& o, std::istream& in){
	std::string inputString{};
	getline(in,inputString);
	std::istringstream inputStream{inputString};
	std::istringstream resultStream{buildOutput(inputStream,9)};
	printLargeNumber(o, resultStream);
}

void calculate(std::ostream& o, std::istream& in, int const scale){
	std::string inputString{};
	getline(in,inputString);
	std::istringstream inputStream{inputString};
	std::istringstream resultStream{buildOutput(inputStream,9)};
	printLargeNumber(o, resultStream, scale);
}