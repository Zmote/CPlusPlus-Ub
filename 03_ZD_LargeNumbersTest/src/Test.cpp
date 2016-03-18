#include "large_nums.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

void testCharCount() {
	std::istringstream i{"Zafer is da man"};
	int output = charc(i);
	ASSERT_EQUAL(12,output);
}

void testCharCountEmptyStream(){
	std::istringstream i{""};
	int output = charc(i);
	ASSERT_EQUAL(0,output);
}

void testAllCharCount(){
	std::istringstream i{"Zafer is da man"};
	int output = allcharc(i);
	ASSERT_EQUAL(15,output);
}

void testAllCharCountEmptyStream(){
	std::istringstream i{""};
	int output = allcharc(i);
	ASSERT_EQUAL(0,output);
}

void testWordCountNormal(){
	std::istringstream i1{"Zafer is a stud."};
	int output = wc(i1);
	ASSERT_EQUAL(4,output);
}

void testWordCountWithWhiteSpaceAtEnd(){
	std::istringstream i{"Zafer Dogan is a student at the Hsr. "};
	int output = wc(i);
	ASSERT_EQUAL(8,output);
}

void testWordCountEmptyLine(){
	std::istringstream i{""};
	int output = wc(i);
	ASSERT_EQUAL(0, output);
}

void testLineCountWithShortFile(){
	std::istringstream ti{"../02_ZD_AlgoEx/text.txt"};
	int output = lc(ti);
	ASSERT_EQUAL(6,output);
}

void testLineCountWithLargeFile(){
	std::istringstream ti{"../02_ZD_AlgoEx/story.txt"};
	int output = lc(ti);
	ASSERT_EQUAL(24,output);
}

void testAllANormal(){
	std::istringstream istr{"Zafer is da man."};
	int output = allac(istr);
	ASSERT_EQUAL(3,output);
}

void testAllAEmptyStream(){
	std::istringstream istr{""};
	int output = allac(istr);
	ASSERT_EQUAL(0,output);
}

void testPrintSingleLargeNumber3(){
	std::ostringstream o{};
	std::string expected{" - \n"
						 "  |\n"
						 " - \n"
						 "  |\n"
						 " - \n"};
	printSingleLNumber(o,3);
	ASSERT_EQUAL(expected, o.str());
}

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



void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	s.push_back(CUTE(testCharCount));
	s.push_back(CUTE(testCharCountEmptyStream));
	s.push_back(CUTE(testAllCharCount));
	s.push_back(CUTE(testAllCharCountEmptyStream));
	s.push_back(CUTE(testWordCountNormal));
	s.push_back(CUTE(testWordCountWithWhiteSpaceAtEnd));
	s.push_back(CUTE(testWordCountEmptyLine));
	s.push_back(CUTE(testLineCountWithShortFile));
	s.push_back(CUTE(testLineCountWithLargeFile));
	s.push_back(CUTE(testAllANormal));
	s.push_back(CUTE(testAllAEmptyStream));
	s.push_back(CUTE(testPrintSingleLargeNumber3));
	s.push_back(CUTE(testPrintLargeNumber333));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



