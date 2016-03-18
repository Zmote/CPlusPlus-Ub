#include "sevensegment.h"
#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>

const std::vector<std::vector<std::string>> Sevensegment::numbers{
	{
		" - ",
		"| |",
		"   ",
		"| |",
		" - "
	},
	{
		"   ",
		"  |",
		"   ",
		"  |",
		"   "
	},
	{
		" - ",
		"  |",
		" - ",
		"|  ",
		" - "
	},
	{
		" - ",
		"  |",
		" - ",
		"  |",
		" - "
	},
	{
		"   ",
		"| |",
		" - ",
		"  |",
		"   "
	},
	{
		" - ",
		"|  ",
		" - ",
		"  |",
		" - "
	},
	{
		" - ",
		"|  ",
		" - ",
		"| |",
		" - "
	},
	{
		" - ",
		"  |",
		"   ",
		"  |",
		"   "
	},
	{
		" - ",
		"| |",
		" - ",
		"| |",
		" - "
	},
	{
		" - ",
		"| |",
		" - ",
		"  |",
		" - "
	},
	{
		" - ",
		"|  ",
		" - ",
		"|  ",
		" - "
	},
	{
		"   ",
		"   ",
		" - ",
		"|  ",
		"   "
	},
	{
		"   ",
		"   ",
		" - ",
		"| |",
		" - "
	},
	{
		"   ",
		"   ",
		"   ",
		"   ",
		"   "
	},
	{
		"   ",
		"   ",
		" - ",
		"   ",
		"   "
	}
};
//--> k�nnte man als Member-Funktion weglassen, da andere ausserhalb
// der Datei diese Methoden nicht benutzen k�nnen, da keine Deklaration
// und als Member-Funktion �berfl�ssig(da es nicht in Kontext der
//Klasse gebraucht werden kann)
int Sevensegment::charMapper(char const inputChar){
switch(inputChar){
	case 'e': return 10;
	case 'r': return 11;
	case 'o': return 12;
	case ' ': return 13;
	case '-': return 14;
	default:
		if(inputChar < '0' || inputChar > '9'){
			throw std::invalid_argument("Invalid argument, non-printable");
		}
		int x = (int)inputChar - '0';
		return x;
	};
}
// Das Gleiche hier auch g�ltig, allgemein
void Sevensegment::drawLine(int i, std::string givenNumber, int scale, std::ostream & o){
	for_each(begin(givenNumber),end(givenNumber),[&](auto j){
		int position;
		try{
			position = charMapper(j);
		}catch(std::invalid_argument &e){
			throw;
		}
		std::string lineBuilder{};
		std::string middleElement{};
		lineBuilder = numbers.at(position).at(i);
		middleElement = numbers.at(position).at(i).at(1);
		for(int k = 0; k < scale; k++){
			lineBuilder.insert(1,middleElement);
		}
		o << lineBuilder;
	});
	o << '\n';
}

void Sevensegment::printLargeNumber(std::ostream &o,std::istream &in){
	std::string givenNumber{};
	getline(in,givenNumber);
	for(int j = 0; j < 5;j++){
		for_each(begin(givenNumber),end(givenNumber),[&](auto i){
			int position;
			try{
				position = charMapper(i);
			}catch(std::invalid_argument &e){
				throw;
			}
			o << numbers.at(position).at(j);
		});
		o << '\n';
	}
}

void Sevensegment::printLargeNumber(std::ostream &o, std::istream &in, int const scale){
	std::string givenNumber{};
	getline(in,givenNumber);
	for(int i = 0; i < 5; i++){
		if(i == 0 || i == 2 || i == 4){
			try{
			drawLine(i, givenNumber, scale, o);
			}catch(std::invalid_argument &e){
				throw;
			}
		}
		if(i == 1 || i == 3){
			for(int z = 0; z < scale;z++){
				try{
				drawLine(i, givenNumber, scale, o);
				}catch(std::invalid_argument &e){
					throw;
				}
			}
		}
	}
}

void Sevensegment::printSingleLNumber(std::ostream &o, std::istream &i){
	int in;
	i >> in;
	if(!i){
		i.clear();
		throw std::invalid_argument("Invalid input, not a number");
	}
	for_each(begin(numbers.at(in)),end(numbers.at(in)),[&](auto i){
		o << i << '\n';
	});
}