#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "BoundedQueue.h"

void test_try_pop_with_experimental_optional(){
	BoundedQueue<int> queue{10};
	for(int i = 0; i < 10; i++){
		queue.push(i);
	}
	ASSERT_EQUAL(9,queue.try_pop());
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	s.push_back(CUTE(test_try_pop_with_experimental_optional));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");

}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}

