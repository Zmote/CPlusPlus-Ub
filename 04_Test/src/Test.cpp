#include "w04algo.h"
#include <sstream>
#include <cmath>
#include <functional>
#include <string>
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

void testWordCount(){
	std::istringstream i{"My name is Zafer."};
	std::ostringstream o{};
	wlist(o,i);
	ASSERT_EQUAL("is\n"
				 "my\n"
				 "name\n"
				 "zafer\n", o.str());
}

void testWordCountertwoSentences(){
	std::istringstream i{"My name is Zafer and zafer loves fish3."};
	std::ostringstream o{};
	wlist(o,i);
	ASSERT_EQUAL("and\n"
				 "fish\n"
				 "is\n"
				 "loves\n"
				 "my\n"
				 "name\n"
				 "zafer\n", o.str());
}

void testBasicFunctionTable(){
	std::ostringstream o{};
	printFunctionTable(o,1,9,4,[](double x){return x + 1;});
	ASSERT_EQUAL("x: 1 3 5 7 9 \n"
				 "f(x): 2 4 6 8 10 \n"
				  ,o.str());
}

void testSimpleCosineFunction(){
	std::ostringstream o{};
	printFunctionTable(o,0,0,0,[](double x){return std::cos(0.0);});
	ASSERT_EQUAL("x: 0 \n"
				 "f(x): 1 \n"
				  ,o.str());
}

void testSimpleSineFunction(){
	std::ostringstream o{};
	printFunctionTable(o,1,1,0,[](double x){return std::sin(x);});
	ASSERT_EQUAL("x: 1 \n"
				 "f(x): 0.841471 \n"
				  ,o.str());
}

void testSimpleSineFunctionWithPi(){
	double pi = std::acos(-1);
	std::ostringstream o{};
	printFunctionTable(o,pi/2,pi/2,0,[](double x){return std::sin(x);});
	ASSERT_EQUAL("x: 1.5708 \n"
				 "f(x): 1 \n"
					  ,o.str());
}

void testSquareFunction(){
	std::ostringstream o{};
	printFunctionTable(o,1.0,11.0,5,[](double x){return x*x;});
	ASSERT_EQUAL("x: 1 3 5 7 9 11 \n"
				 "f(x): 1 9 25 49 81 121 \n"
					  ,o.str());
}

void test0toPiIn19Steps(){

}

void lowerFirstCharacter() {
	std::string str("Hello!");
	ASSERT_EQUAL(1, countingToLower(str));
	ASSERT_EQUAL("hello!", str);
}

void lowerSeveralCharacters() {
	std::string str("Hello World, its ME!");
	ASSERT_EQUAL(4, countingToLower(str));
	ASSERT_EQUAL("hello world, its me!", str);
}

void lowerNone() {
	std::string str("no uppercase characters here");
	ASSERT_EQUAL(0, countingToLower(str));
	ASSERT_EQUAL("no uppercase characters here", str);
}

void lowerAll() {
	std::string str("LOL");
	ASSERT_EQUAL(3, countingToLower(str));
	ASSERT_EQUAL("lol", str);
}

void lowerEmpty() {
	std::string str("");
	ASSERT_EQUAL(0, countingToLower(str));
	ASSERT_EQUAL("", str);
}

void umlautsAreNotChanged() {
	std::string str("���");
	ASSERT_EQUAL(0, countingToLower(str));
	ASSERT_EQUAL("���", str);
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	s.push_back(CUTE(testWordCount));
	s.push_back(CUTE(testWordCountertwoSentences));
	s.push_back(CUTE(lowerFirstCharacter));
	s.push_back(CUTE(lowerSeveralCharacters));
	s.push_back(CUTE(lowerNone));
	s.push_back(CUTE(lowerAll));
	s.push_back(CUTE(lowerEmpty));
	s.push_back(CUTE(umlautsAreNotChanged));
	s.push_back(CUTE(testBasicFunctionTable));
	s.push_back(CUTE(testSimpleCosineFunction));
	s.push_back(CUTE(testSimpleSineFunction));
	s.push_back(CUTE(testSimpleSineFunctionWithPi));
	s.push_back(CUTE(testSquareFunction));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



