#include "Ansi.h"
#include <iostream>
using namespace Ansi;
//Ignore errors
std::string Pos(unsigned l, unsigned c) {
    return ESCAPE + std::to_string(l) + ";" + std::to_string(c) + "H";
}

std::string Clear(){
	return ESCAPE + "2J";
}
std::string ForeColor(unsigned color){
	return ESCAPE + std::to_string(color) + "m";
}
std::string BackColor(unsigned color){
	return ESCAPE + std::to_string(color) + "m";
}
std::string Bold(){
	return ESCAPE + std::to_string(1) + "m";
}
std::string AttributeOff(){
	return ESCAPE + std::to_string(0) + "m";
}

std::string Home(){
	 return ESCAPE + std::to_string(0) + ";" + std::to_string(0) + "H";
}

std::string Up(unsigned n){
	return ESCAPE + std::to_string(n) + "A";
}

std::string Down(unsigned n){
	return ESCAPE + std::to_string(n) + "B";
}
std::string Right(unsigned n){
	return ESCAPE + std::to_string(n) + "C";
}
std::string Left(unsigned n){
	return ESCAPE + std::to_string(n) + "D";
}