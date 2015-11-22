#include "word.h"
#include "kwic.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

void testSmallerThanOperator(){
Word myword_1{"Zafer"};
Word myword_2{"Niyazi"};
ASSERT_EQUAL(true,myword_2<myword_1);
}

void testGreaterThanOperator(){
Word myword_1{"Zafer"};
Word myword_2{"Niyazi"};
ASSERT_EQUAL(false,myword_2>myword_1);
}

void testEqualToOperator(){
Word myword_1{"Zafer"};
Word myword_2{"Zafer"};
ASSERT_EQUAL(true,myword_2==myword_1);
}

void testNotEqualToOperator(){
Word myword_1{"Zafer"};
Word myword_2{"Niyazi"};
ASSERT_EQUAL(true,myword_2!=myword_1);
}

void testGreaterThanOrEqualOperator(){
Word myword_1{"Zafer"};
Word myword_2{"Zbfer"};
ASSERT_EQUAL(true,myword_2>=myword_1);
}

void testSmallerThanOrEqualOperator(){
Word myword_1{"Zafer"};
Word myword_2{"Zbfer"};
ASSERT_EQUAL(true,myword_1<=myword_2);
}

void testSimpleWordPerConstructor(){
Word myword{"Zafer"};
std::ostringstream o{};
o << myword;
ASSERT_EQUAL("Zafer", o.str());
}
void testInvalidWordPerConstructor1(){
ASSERT_THROWS(Word myword{"Zafer2"},std::invalid_argument);
}
void testInvalidWordPerConstructor2(){
ASSERT_THROWS(Word myword{"?!Cucumber"},std::invalid_argument);
}
void testInvalidWordPerConstructor3(){
ASSERT_THROWS(Word myword{" Zafer"},std::invalid_argument);
}
void testMultipleWordsConstructor(){
ASSERT_THROWS(Word myword{"Zafer is da man"},std::invalid_argument);
}
void testEmptyWordConstructor(){
ASSERT_THROWS(Word myword{""},std::invalid_argument);
}
void testDefaultWordConstructor(){
Word myword{};
std::ostringstream o{};
o << myword;
ASSERT_EQUAL("",o.str());
}
void testSimpleWordPerStream(){
std::istringstream i{"Zafer"};
std::ostringstream o{};
Word myword{};
i >> myword;
o << myword;
ASSERT_EQUAL("Zafer",o.str());
}
void testInvalidWordPerStream1(){
std::istringstream i{"compl33tely"};
std::ostringstream o{};
Word myword{};
i >> myword;
o << myword;
ASSERT_EQUAL("compl",o.str());
}
void testInvalidWordPerStream2(){
std::istringstream i{" Hallo!"};
std::ostringstream o{};
Word myword{};
i >> myword;
o << myword;
ASSERT_EQUAL("Hallo",o.str());
}
void testInvalidWordPerStream3(){
std::istringstream i{" 33 234"};
std::ostringstream o{};
Word myword{};
i >> myword;
o << myword;
ASSERT_EQUAL("",o.str());
}

void testMultipleWordsStream(){
std::istringstream i{"compl33tely ~ weird !!?!! 4matted in_put"};
std::ostringstream o{};
Word myword{};
while(i){
	i>>myword;
	o << myword << '\n';
}
ASSERT_EQUAL("compl\ntely\nweird\nmatted\nin\nput\n",o.str());
}

void testMultipleWordsStream2(){
std::istringstream i{"Hallo, Welt! 3.32 Zafer ist hier"};
std::ostringstream o{};
Word myword{};
i >> myword;
i >> myword;
o << myword;
ASSERT_EQUAL("Welt",o.str());
}

void testEmptyWordStream(){
std::istringstream i{""};
Word myword{};
i >> myword;
std::ostringstream o{};
o << myword;
ASSERT_EQUAL("",o.str());
}

void testWordEndOfInputStream(){
std::istringstream i{" "};
std::ostringstream o{};
Word myword{};
i >> myword;
o << myword;
ASSERT_EQUAL("",o.str());
}

void testPrint(){
Word myword{"Zafer"};
std::ostringstream o{};
myword.print(o);
ASSERT_EQUAL("Zafer",o.str());
}

void testSimpleKwic(){
std::istringstream i{"Do it"};
std::ostringstream o{};
kwic(o,i);
ASSERT_EQUAL("Do it \nit Do \n",o.str());
}

void testKwicWithInvalidCharacters(){
std::istringstream i{"compl33tely ~ weird !!?!! 4matted in_put"};
std::ostringstream o{};
kwic(o,i);
ASSERT_EQUAL("compl tely weird matted in put \n"
			"in put compl tely weird matted \n"
			"matted in put compl tely weird \n"
			"put compl tely weird matted in \n"
			"tely weird matted in put compl \n"
			"weird matted in put compl tely \n",o.str());
}

void testKwicWithOneWord(){
std::istringstream i{"Zafer"};
std::ostringstream o{};
kwic(o,i);
ASSERT_EQUAL("Zafer \n",o.str());
}

void testKwicWithOneSentence(){
std::istringstream i{"My name is Zafer and this better work"};
std::ostringstream o{};
kwic(o,i);
ASSERT_EQUAL("and this better work My name is Zafer \n"
			"better work My name is Zafer and this \n"
			"is Zafer and this better work My name \n"
			"My name is Zafer and this better work \n"
			"name is Zafer and this better work My \n"
			"this better work My name is Zafer and \n"
			"work My name is Zafer and this better \n"
			"Zafer and this better work My name is \n",o.str());
}

void testKwichWithTwoSentences(){
std::istringstream i{"this is a test\nthis is another test\n"};
std::ostringstream o{};
kwic(o,i);
ASSERT_EQUAL("a test this is \n"
			"another test this is \n"
			"is a test this \n"
			"is another test this \n"
			"test this is a \n"
			"test this is another \n"
			"this is a test \n"
			"this is another test \n",o.str());
}

void testKwicWithTwoWordsOnSeperateLines(){
std::istringstream i{"Do\nit\n"};
std::ostringstream o{};
kwic(o,i);
ASSERT_EQUAL("Do \nit \n",o.str());
}

void testKwichWithEmptyInput(){
std::istringstream i{""};
std::ostringstream o{};
kwic(o,i);
ASSERT_EQUAL("",o.str());
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	s.push_back(CUTE(testSmallerThanOperator));
	s.push_back(CUTE(testGreaterThanOperator));
	s.push_back(CUTE(testEqualToOperator));
	s.push_back(CUTE(testNotEqualToOperator));
	s.push_back(CUTE(testGreaterThanOrEqualOperator));
	s.push_back(CUTE(testSmallerThanOrEqualOperator));
	s.push_back(CUTE(testSimpleWordPerConstructor));
	s.push_back(CUTE(testInvalidWordPerConstructor1));
	s.push_back(CUTE(testInvalidWordPerConstructor2));
	s.push_back(CUTE(testInvalidWordPerConstructor3));
	s.push_back(CUTE(testMultipleWordsConstructor));
	s.push_back(CUTE(testEmptyWordConstructor));
	s.push_back(CUTE(testDefaultWordConstructor));
	s.push_back(CUTE(testSimpleWordPerStream));
	s.push_back(CUTE(testInvalidWordPerStream1));
	s.push_back(CUTE(testInvalidWordPerStream2));
	s.push_back(CUTE(testInvalidWordPerStream3));
	s.push_back(CUTE(testMultipleWordsStream));
	s.push_back(CUTE(testMultipleWordsStream2));
	s.push_back(CUTE(testEmptyWordStream));
	s.push_back(CUTE(testWordEndOfInputStream));
	s.push_back(CUTE(testPrint));
	s.push_back(CUTE(testSimpleKwic));
	s.push_back(CUTE(testKwicWithInvalidCharacters));
	s.push_back(CUTE(testKwicWithOneWord));
	s.push_back(CUTE(testKwicWithOneSentence));
	s.push_back(CUTE(testKwichWithTwoSentences));
	s.push_back(CUTE(testKwicWithTwoWordsOnSeperateLines));
	s.push_back(CUTE(testKwichWithEmptyInput));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



