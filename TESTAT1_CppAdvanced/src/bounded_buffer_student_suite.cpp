#include "bounded_buffer_student_suite.h"
#include "cute.h"
#include "BoundedBuffer.h"

//void test_default_constructed_const_int_buffer_of_size_thousand_is_empty_with_more_info() {
//	BoundedBuffer<int, 1000> const buffer{};
//	std::cout << "buffer size: " << buffer.size() << "\n";
//	std::cout << "buffer empty: " << buffer.empty() << "\n";
//	ASSERTM("New buffer should be empty", buffer.empty());
//}
//
//void test_default_constructed_const_int_buffer_of_size_zero_is_empty_with_more_info() {
//	BoundedBuffer<int, 0> const buffer{};
//	std::cout << "buffer size: " << buffer.size() << "\n";
//	std::cout << "buffer empty: " << buffer.empty() << "\n";
//	ASSERTM("New buffer should be empty", buffer.empty());
//}

cute::suite make_suite_bounded_buffer_student_suite(){
	cute::suite s;
//	s.push_back(CUTE(test_default_constructed_const_int_buffer_of_size_thousand_is_empty_with_more_info));
//	s.push_back(CUTE(test_default_constructed_const_int_buffer_of_size_zero_is_empty_with_more_info));
	return s;
}


