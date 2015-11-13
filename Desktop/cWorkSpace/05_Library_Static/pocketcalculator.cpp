#include "calc.h"
#include "sevensegment.h"
#include "pocketcalculator.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
//TODO: falls man nach +2, +2 wieder eintippt: 2+2 und = 4 erhalten m�chte, m�sste man noch einen Zwischenschritt einf�gen
std::string Pocketcalculator::first{""};
bool Pocketcalculator::checkInput(std::string &str, unsigned int screenDigitLimit){
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
	return invalidOperand || NaNCounter >= 2;
}

std::string Pocketcalculator::buildOutput(std::istringstream &inputStream, unsigned int screenDigitLimit){
	std::string str{(std::istreambuf_iterator<char>(inputStream)),
		(std::istreambuf_iterator<char>())};
	int errValue = INT_MAX;
	int result;
	if(checkInput(str,screenDigitLimit)){
		result = errValue;
	}else{
		std::istringstream inStream{str};
		try{
			result = Calculator::calc(inStream);
			Pocketcalculator::first = std::to_string(result);
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

void Pocketcalculator::calculate(std::ostream& o, std::istream& in){
	std::string inputString{};
	getline(in,inputString);
	inputString.insert(0,Pocketcalculator::first);
	std::istringstream inputStream{inputString};
	std::istringstream resultStream{buildOutput(inputStream,9)};
	Sevensegment::printLargeNumber(o, resultStream);
}

void Pocketcalculator::calculate(std::ostream& o, std::istream& in, int const scale){
	std::string inputString{};
	getline(in,inputString);
	inputString.insert(0,Pocketcalculator::first);
	std::istringstream inputStream{inputString};
	std::istringstream resultStream{buildOutput(inputStream,9)};
	Sevensegment::printLargeNumber(o, resultStream, scale);
}