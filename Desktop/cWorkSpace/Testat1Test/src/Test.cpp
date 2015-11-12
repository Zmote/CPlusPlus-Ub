#include "calc.h"
#include "sevensegment.h"
#include "pocketcalculator.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

/******** Calc Tests**********/

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

void testDivisionThroughZero(){
	ASSERT_THROWS(calc(50,0,'/'),std::logic_error);
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

void testModulo(){
	std::ostringstream o{};
	o << calc(100,2,'%');
	ASSERT_EQUAL("0",o.str());
}

void testModuloWithZero(){
	ASSERT_THROWS(calc(20,0,'%'),std::logic_error);
}

void testCalcInvalidInput(){
	ASSERT_THROWS(calc(0,0,'c'),std::invalid_argument);
}

/******** Sevensegment Tests**********/
void testPrintLargeNumber333(){
	std::ostringstream o{};
	std::istringstream in{"333"};
	printLargeNumber(o,in);
	std::string expected{" -  -  - \n"
						 "  |  |  |\n"
						 " -  -  - \n"
						 "  |  |  |\n"
						 " -  -  - \n"
	};
	ASSERT_EQUAL(expected, o.str());
}

void testPrintLargeNumberInvalidArgument(){
	std::ostringstream o{};
	std::istringstream in{"abc"};
	ASSERT_THROWS(printLargeNumber(o,in), std::invalid_argument);
}

void testPrintLargeNumberScaled2InvalidArgument(){
	std::ostringstream o{};
	std::istringstream in{"abc"};
	ASSERT_THROWS(printLargeNumber(o,in,2), std::invalid_argument);
}

void testPrintSingleLargeNumber3(){
	std::ostringstream o{};
	std::istringstream in{"3"};
	std::string expected{" - \n"
						 "  |\n"
						 " - \n"
						 "  |\n"
						 " - \n"};
	printLargeNumber(o,in);
	ASSERT_EQUAL(expected, o.str());
}

void testPrintSingleLNumber3(){
	std::ostringstream o{};
	std::istringstream in{"3"};
	std::string expected{" - \n"
						 "  |\n"
						 " - \n"
						 "  |\n"
						 " - \n"};
	printSingleLNumber(o,in);
	ASSERT_EQUAL(expected, o.str());
}

void testPrintSingleLNumberInvalidInput(){
	std::ostringstream o{};
	std::istringstream in{"a"};
	ASSERT_THROWS(printSingleLNumber(o,in),std::invalid_argument);
}

void testPrintLargeNumberMinus33(){
	std::ostringstream o{};
	std::istringstream in{"-33"};
	printLargeNumber(o,in);
	std::string expected{"    -  - \n"
						 "     |  |\n"
						 " -  -  - \n"
						 "     |  |\n"
						 "    -  - \n"
	};
	ASSERT_EQUAL(expected, o.str());
}

void testPrintLargeNumber333Scaled2(){
	std::ostringstream o{};
		std::istringstream in{"333"};
		printLargeNumber(o,in,2);
		std::string expected{
							 " ---  ---  --- \n"
							 "    |    |    |\n"
							 "    |    |    |\n"
							 " ---  ---  --- \n"
							 "    |    |    |\n"
							 "    |    |    |\n"
							 " ---  ---  --- \n"
		};
		ASSERT_EQUAL(expected, o.str());
}

/******** PocketCalculator Tests**********/

void testCalculatorInvalidInput(){
	std::ostringstream o{};
	std::istringstream i{"2223334441"};
	calculate(o,i);
	std::string expected{
						 "             -             \n"
						 "            |              \n"
						 "             -  -  -  -  - \n"
						 "            |  |  |  | ||  \n"
						 "             -        -    \n"
	};
	ASSERT_EQUAL(expected, o.str());
}

void testCalculatorInvalidInput2(){
	std::ostringstream o{};
	std::istringstream i{"2223334441+234234-323442/2342"};
	calculate(o,i);
	std::string expected{
						 "             -             \n"
						 "            |              \n"
						 "             -  -  -  -  - \n"
						 "            |  |  |  | ||  \n"
						 "             -        -    \n"
	};
	ASSERT_EQUAL(expected, o.str());
}

void testCalculatorInvalidInput3(){
	std::ostringstream o{};
	std::istringstream i{"abcd+foo"};
	calculate(o,i);
	std::string expected{
						 "             -             \n"
						 "            |              \n"
						 "             -  -  -  -  - \n"
						 "            |  |  |  | ||  \n"
						 "             -        -    \n"
	};
	ASSERT_EQUAL(expected, o.str());
}

void testCalculatorInvalidOperand(){
	std::ostringstream o{};
	std::istringstream i{"2223334441+2323"};
	calculate(o,i);
	std::string expected{
						 "             -             \n"
						 "            |              \n"
						 "             -  -  -  -  - \n"
						 "            |  |  |  | ||  \n"
						 "             -        -    \n"
	};
	ASSERT_EQUAL(expected, o.str());
}

void testCalculatorInvalidOperator(){
	std::ostringstream o{};
	std::istringstream i{"222c2323"};
	calculate(o,i);
	std::string expected{
						 "             -             \n"
						 "            |              \n"
						 "             -  -  -  -  - \n"
						 "            |  |  |  | ||  \n"
						 "             -        -    \n"
	};
	ASSERT_EQUAL(expected, o.str());
}

void testCalculatorSignedOperand(){
	std::ostringstream o{};
	std::istringstream i{"-3+3"};
	calculate(o,i);
	std::string expected{
						 "             -             \n"
						 "            |              \n"
						 "             -  -  -  -  - \n"
						 "            |  |  |  | ||  \n"
						 "             -        -    \n"
	};
	ASSERT_EQUAL(expected, o.str());
}

void testCalculatorSimpleAddition(){
	std::ostringstream o{};
	std::istringstream i{"2+1"};
	calculate(o,i);
	std::string expected{
						 "                         - \n"
						 "                          |\n"
						 "                         - \n"
						 "                          |\n"
						 "                         - \n"
	};
	ASSERT_EQUAL(expected, o.str());
}

void testCalculatorSimpleMultiplication(){
	std::ostringstream o{};
	std::istringstream i{"3*1"};
	calculate(o,i);
	std::string expected{
						 "                         - \n"
						 "                          |\n"
						 "                         - \n"
						 "                          |\n"
						 "                         - \n"
	};
	ASSERT_EQUAL(expected, o.str());
}

void testCalculatorSimpleDivision(){
	std::ostringstream o{};
	std::istringstream i{"6/2"};
	calculate(o,i);
	std::string expected{
						 "                         - \n"
						 "                          |\n"
						 "                         - \n"
						 "                          |\n"
						 "                         - \n"
	};
	ASSERT_EQUAL(expected, o.str());
}

void testCalculatorSimpleSubtraction(){
	std::ostringstream o{};
	std::istringstream i{"6-3"};
	calculate(o,i);
	std::string expected{
						 "                         - \n"
						 "                          |\n"
						 "                         - \n"
						 "                          |\n"
						 "                         - \n"
	};
	ASSERT_EQUAL(expected, o.str());
}

void testCalculatorSimpleSubtractionNegative(){
	std::ostringstream o{};
	std::istringstream i{"3-6"};
	calculate(o,i);
	std::string expected{
						 "                         - \n"
						 "                          |\n"
						 "                      -  - \n"
						 "                          |\n"
						 "                         - \n"
	};
	ASSERT_EQUAL(expected, o.str());
}

void testCalculatorSimpleModulo(){
	std::ostringstream o{};
	std::istringstream i{"7%4"};
	calculate(o,i);
	std::string expected{
						 "                         - \n"
						 "                          |\n"
						 "                         - \n"
						 "                          |\n"
						 "                         - \n"
	};
	ASSERT_EQUAL(expected, o.str());
}

void testCalculatorSimpleDivisionThroughZero(){
	std::ostringstream o{};
	std::istringstream i{"3/0"};
	calculate(o,i);
	std::string expected{
						 "             -             \n"
						 "            |              \n"
						 "             -  -  -  -  - \n"
						 "            |  |  |  | ||  \n"
						 "             -        -    \n"
	};
	ASSERT_EQUAL(expected, o.str());
}

void testCalculatorSimpleModuloWithZero(){
	std::ostringstream o{};
	std::istringstream i{"3%0"};
	calculate(o,i);
	std::string expected{
						 "             -             \n"
						 "            |              \n"
						 "             -  -  -  -  - \n"
						 "            |  |  |  | ||  \n"
						 "             -        -    \n"
	};
	ASSERT_EQUAL(expected, o.str());
}

void testCalculatorScaled2(){
	std::ostringstream o{};
	std::istringstream i{"222+111"};
	calculate(o,i,2);
	std::string expected{
								 "                               ---  ---  --- \n"
								 "                                  |    |    |\n"
								 "                                  |    |    |\n"
								 "                               ---  ---  --- \n"
								 "                                  |    |    |\n"
								 "                                  |    |    |\n"
								 "                               ---  ---  --- \n"
			};
	ASSERT_EQUAL(expected, o.str());
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	s.push_back(CUTE(testMultiplication));
	s.push_back(CUTE(testDivision));
	s.push_back(CUTE(testAddition));
	s.push_back(CUTE(testSubtraction));
	s.push_back(CUTE(testDivisionThroughZero));
	s.push_back(CUTE(testModulo));
	s.push_back(CUTE(testModuloWithZero));
	s.push_back(CUTE(testPrintLargeNumber333));
	s.push_back(CUTE(testPrintSingleLargeNumber3));
	s.push_back(CUTE(testCalcInvalidInput));
	s.push_back(CUTE(testPrintLargeNumberMinus33));
	s.push_back(CUTE(testPrintLargeNumber333Scaled2));
	s.push_back(CUTE(testCalculatorInvalidInput));
	s.push_back(CUTE(testCalculatorSimpleAddition));
	s.push_back(CUTE(testCalculatorSimpleMultiplication));
	s.push_back(CUTE(testCalculatorSimpleDivision));
	s.push_back(CUTE(testCalculatorSimpleSubtraction));
	s.push_back(CUTE(testCalculatorSimpleModulo));
	s.push_back(CUTE(testCalculatorSimpleDivisionThroughZero));
	s.push_back(CUTE(testCalculatorSimpleModuloWithZero));
	s.push_back(CUTE(testCalculatorSimpleSubtractionNegative));
	s.push_back(CUTE(testCalculatorSignedOperand));
	s.push_back(CUTE(testCalculatorInvalidOperand));
	s.push_back(CUTE(testCalculatorInvalidInput2));
	s.push_back(CUTE(testCalculatorInvalidOperator));
	s.push_back(CUTE(testCalculatorInvalidInput3));
	s.push_back(CUTE(testCalculatorScaled2));
	s.push_back(CUTE(testPrintLargeNumberInvalidArgument));
	s.push_back(CUTE(testPrintLargeNumberScaled2InvalidArgument));
	s.push_back(CUTE(testPrintSingleLNumber3));
	s.push_back(CUTE(testPrintSingleLNumberInvalidInput));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



