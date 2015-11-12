#include "Date.h"
#include <iostream>

int main(){
	Date adate{2014,Date::November,12};
	Date bdate{Date::Dezember,13,2015};
	adate.print(std::cout);
	std::cout << "\n" << adate.day_of_week() << "\n";
	bdate.print(std::cout);
	std::cout << "\n" << bdate.day_of_week();
}
