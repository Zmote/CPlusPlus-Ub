#include "Ansi.h"
#include <iostream>
#include <string>
//Ignore errors
std::string Ansi::Pos(unsigned l, unsigned c) {
    return ESCAPE + std::to_string(l) + ";" + std::to_string(c) + "H";
}

std::string Ansi::Clear(){
	return ESCAPE + "2J";
}

std::string Ansi::Blink(){
	return ESCAPE + std::to_string(5) + "m";
}
std::string Ansi::ForeColor(unsigned color){
	return ESCAPE + std::to_string(color) + "m";
}
std::string Ansi::BackColor(unsigned color){
	return ESCAPE + std::to_string(color) + "m";
}
std::string Ansi::Bold(){
	return ESCAPE + std::to_string(1) + "m";
}
std::string Ansi::AttributeOff(){
	return ESCAPE + std::to_string(0) + "m";
}

std::string Ansi::Home(){
	 return ESCAPE + std::to_string(0) + ";" + std::to_string(0) + "H";
}

std::string Ansi::Up(unsigned n){
	return ESCAPE + std::to_string(n) + "A";
}

std::string Ansi::Down(unsigned n){
	return ESCAPE + std::to_string(n) + "B";
}
std::string Ansi::Right(unsigned n){
	return ESCAPE + std::to_string(n) + "C";
}
std::string Ansi::Left(unsigned n){
	return ESCAPE + std::to_string(n) + "D";
}
