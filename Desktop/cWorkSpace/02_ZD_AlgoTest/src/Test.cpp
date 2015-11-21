#include "algo_head.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

void testCharCount() {
	std::istringstream i1{"Zafer is da man"};
	std::istringstream i2{""};
	int output = charc(i1);
	ASSERT_EQUAL(12,output);
	output = charc(i2);
	ASSERT_EQUAL(0,output);
}

void testAllCharCount(){
	std::istringstream i1{"Zafer is da man"};
	std::istringstream i2{""};
	int output = allcharc(i1);
	ASSERT_EQUAL(15,output);
	output = allcharc(i2);
	ASSERT_EQUAL(0,output);
}

void testWordCount(){
	std::istringstream i1{"Zafer is a stud."};
	std::istringstream i2{""};
	std::istringstream i3{"Zafer Dogan is a student at the Hsr. "};
	int output = wc(i1);
	ASSERT_EQUAL(4,output);
	output = wc(i2);
	ASSERT_EQUAL(0, output);
	output = wc(i3);
	ASSERT_LESS(8,output);
}

void testLineCount(){
	std::istringstream i1{"../02_ZD_AlgoEx/text.txt"};
	std::istringstream i2{"../02_ZD_AlgoEx/story.txt"};
	int output = lc(i1);
	ASSERT_EQUAL(6,output);
	output = lc(i2);
	ASSERT_EQUAL(22,output);
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(testCharCount));
	s.push_back(CUTE(testAllCharCount));
	s.push_back(CUTE(testWordCount));
	s.push_back(CUTE(testLineCount));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



