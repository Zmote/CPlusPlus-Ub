#include "word.h"
#include "kwic.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

//TODO: kwic tests
//TODO: more word-tests, new behaviour
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
Word myword{};
i >> myword;
std::ostringstream o{};
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
Word myword{};
i >> myword;
std::ostringstream o{};
o << myword;
ASSERT_EQUAL("Hallo",o.str());
}
void testInvalidWordPerStream3(){
std::istringstream i{" 33 234"};
Word myword{};
i >> myword;
std::ostringstream o{};
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
Word myword{};
i >> myword;
i >> myword;
std::ostringstream o{};
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
Word myword{};
i >> myword;
std::ostringstream o{};
o << myword;
ASSERT_EQUAL("",o.str());
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
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
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



