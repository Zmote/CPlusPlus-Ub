#include "w06_algo.h"
#include "Ansi.h"
#include <unistd.h>
#include <iostream>
//cevelop error, does build
enum class Switch::State: unsigned short{ON, OFF, BLINKING};

void Switch::pressButton(){
	switch(currentState){
	case State::ON:
		currentState = State::BLINKING;
		std::cout << Ansi::Blink();
		break;
	case State::OFF:
		currentState = State::ON;
		std::cout << Ansi::ForeColor(Ansi::fwhite);
		std::cout << Ansi::BackColor(Ansi::bblack);
		break;
	case State::BLINKING:
		currentState = State::OFF;
		std::cout << Ansi::AttributeOff();
		break;
	}
}

Switch::Switch():currentState{Switch::State::OFF}{

}
