#include "calculator.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <ostream>

void testMultiplication() {
	std::ostringstream o{};
	o << calc(5,5,'*');
	ASSERT_EQUAL("25",o.str());
}

void testDivision(){
	std::ostringstream o{};
	o << calc(125,5,'/');
	ASSERT_EQUAL("25",o.str());
}

void testAddition(){
	std::ostringstream o{};
	o << calc(25,100,'+');
	ASSERT_EQUAL("125",o.str());
}

void testSubtraction(){
	std::ostringstream o{};
	o << calc(100, 45, '-');
	ASSERT_EQUAL("55",o.str());
}

void testDivisionThroughZero(){
	std::ostringstream o{};
	try{
		o << calc(50,0,'/');
	}catch(std::exception& e){
		ASSERT_EQUAL("Can't divide through zero\n",e.what());
	}
}

void testModuloWithZero(){
	std::ostringstream o{};
		try{
			o << calc(20,0,'%');
		}catch(std::exception& e){
			ASSERT_EQUAL("Second argument of modulo can't be zero\n",e.what());
		}
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	s.push_back(CUTE(testMultiplication));
	s.push_back(CUTE(testDivision));
	s.push_back(CUTE(testAddition));
	s.push_back(CUTE(testSubtraction));
	s.push_back(CUTE(testDivisionThroughZero));
	s.push_back(CUTE(testModuloWithZero));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



