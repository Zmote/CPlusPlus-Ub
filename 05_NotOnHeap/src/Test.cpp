#include "not_on_heap.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <vector>
#include <memory>


void test_local_instance_creation_of_not_on_heap(){
	noh_extended noh{};
	ASSERT_EQUAL(10,noh.x);
}

void test_on_heap_creation_with_new_not_possible(){
	ASSERT_THROWS(new noh_extended{},std::bad_alloc);
}

void test_on_heap_array_creation_with_new_not_possible(){
	ASSERT_THROWS(new noh_extended[5]{},std::bad_alloc);
}

void test_vector_with_not_on_heap_stil_works(){
	std::vector<not_on_heap> vec{};
	vec.push_back(noh_extended{});
	vec.push_back(noh_extended{});
	ASSERT_EQUAL(2,vec.size());
}

void test_attempt_class_with_std_make_unique(){
	ASSERT_THROWS(std::make_unique<not_on_heap>(),std::bad_alloc);
}

void test_new_not_on_heap_as_parameter_for_std_unique_ptr(){
	ASSERT_THROWS(std::unique_ptr<not_on_heap>{new not_on_heap()},std::bad_alloc);
}

void test_std_make_shared_to_allocate_not_on_heap_on_heap(){
	//well, interesting, apparently you can allocate on the heap with a shared_ptr!!
	std::shared_ptr<not_on_heap> noh_shared_ptr = std::make_shared<not_on_heap>();
	ASSERT(noh_shared_ptr != nullptr);
}

void test_create_new_object_and_then_rassign_cheat(){
	//ask this part, what was really meant to do?
	not_on_heap * ptr = new not_on_heap[5]{};
	ASSERT(ptr != nullptr);
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	s.push_back(CUTE(test_local_instance_creation_of_not_on_heap));
	s.push_back(CUTE(test_on_heap_creation_with_new_not_possible));
	s.push_back(CUTE(test_on_heap_array_creation_with_new_not_possible));
	s.push_back(CUTE(test_vector_with_not_on_heap_stil_works));
	s.push_back(CUTE(test_attempt_class_with_std_make_unique));
	s.push_back(CUTE(test_new_not_on_heap_as_parameter_for_std_unique_ptr));
	s.push_back(CUTE(test_std_make_shared_to_allocate_not_on_heap_on_heap));
	s.push_back(CUTE(test_create_new_object_and_then_rassign_cheat));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}


