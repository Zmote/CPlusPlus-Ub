#include "bounded_queue_student_suite.h"

#include "BoundedQueue.h"
#include "cute.h"
#include <thread>

void test_one_thread_calling_push_or_pop(){
	BoundedQueue<int> queue{5};
	int value{3};
	std::thread t{[&]{queue.push(value);}};
	t.join();
	ASSERT_EQUAL(1,queue.size());
}

void test_one_thread_calls_push_other_thread_calls_pop(){
	BoundedQueue<int> queue{5};
	int value{3};
	std::thread t1{[&]{queue.push(value);}};
	std::thread t2{[&]{queue.pop();}};
	t1.join();
	t2.join();
	ASSERT_EQUAL(0,queue.size());
}

void test_multiple_threads_calling_push_on_empty_queue(){
	BoundedQueue<int> queue{5};
	int value{3};
	std::thread t1{[&]{queue.push(value);}};
	std::thread t2{[&]{queue.push(value);}};
	std::thread t3{[&]{queue.push(value);}};
	std::thread t4{[&]{queue.push(value);}};
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	ASSERT_EQUAL(4,queue.size());
}

void test_multiple_threads_calling_push_on_full_queue(){
	BoundedQueue<int> queue{5};
	int value{3};
	for(int i=0;i<5;i++){
		queue.push(value);
	}
	std::thread t1{[&]{queue.try_push(value);}};
	std::thread t2{[&]{queue.try_push(value);}};
	std::thread t3{[&]{queue.try_push(value);}};
	std::thread t4{[&]{queue.try_push(value);}};
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	ASSERT_EQUAL(5,queue.size());
}

void test_multiple_threads_calling_pop_on_empty_queue(){
	BoundedQueue<int> queue{5};
	int value{3};
	std::thread t1{[&]{queue.try_pop(value);}};
	std::thread t2{[&]{queue.try_pop(value);}};
	std::thread t3{[&]{queue.try_pop(value);}};
	std::thread t4{[&]{queue.try_pop(value);}};
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	ASSERT_EQUAL(0,queue.size());
}

void test_multiple_threads_calling_pop_on_full_queue(){
	BoundedQueue<int> queue{5};
	int value{3};
	for(int i = 0;i < 5;i++){
		queue.push(value);
	}
	std::thread t1{[&]{queue.try_pop(value);}};
	std::thread t2{[&]{queue.try_pop(value);}};
	std::thread t3{[&]{queue.try_pop(value);}};
	std::thread t4{[&]{queue.try_pop(value);}};
	std::thread t5{[&]{queue.try_pop(value);}};
	std::thread t6{[&]{queue.try_pop(value);}};
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	ASSERT_EQUAL(0,queue.size());
}

void test_multiple_threads_calling_pop_on_partially_full_queue_with_insufficent_items(){
	BoundedQueue<int> queue{5};
	int value{3};
	for(int i = 0;i < 3;i++){
		queue.push(value);
	}
	std::thread t1{[&]{queue.try_pop(value);}};
	std::thread t2{[&]{queue.try_pop(value);}};
	std::thread t3{[&]{queue.try_pop(value);}};
	std::thread t4{[&]{queue.try_pop(value);}};
	std::thread t5{[&]{queue.try_pop(value);}};
	std::thread t6{[&]{queue.try_pop(value);}};
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	ASSERT_EQUAL(0,queue.size());
}

void test_multiple_threads_calling_push_while_one_calls_pop_on_empty_queue(){
	//In rare cases, this test might fail(because pop is execute first)
	//how could I do this check better, + is it testat relevant?
	//all following tests suffer from the same problem
	BoundedQueue<int> queue{5};
	int value{3};
	std::thread t1{[&]{queue.try_push(value);}};
	std::thread t2{[&]{queue.try_push(value);}};
	std::thread t3{[&]{queue.try_push(value);}};
	std::thread t4{[&]{queue.try_push(value);}};
	std::thread t5{[&]{queue.try_push(value);}};
	std::thread t6{[&]{queue.try_pop(value);}};
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	ASSERT_EQUAL(4,queue.size());
}

void test_multiple_threads_calling_push_while_one_calls_pop_on_full_queue(){
	BoundedQueue<int> queue{5};
	int value{3};
	for(int i = 0; i<5;i++){
		queue.push(value);
	}
	std::thread t6{[&]{queue.try_pop(value);}};
	std::thread t1{[&]{queue.try_push(value);}};
	std::thread t2{[&]{queue.try_push(value);}};
	std::thread t3{[&]{queue.try_push(value);}};
	std::thread t4{[&]{queue.try_push(value);}};
	std::thread t5{[&]{queue.try_push(value);}};
	t6.join();
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	ASSERT_EQUAL(5,queue.size());
}

void test_multiple_threads_push_while_multiple_threads_call_pop_on_empty_queue(){
	BoundedQueue<int> queue{5};
	int value{3};
	std::thread t1{[&]{queue.push(value);}};
	std::thread t2{[&]{queue.push(value);}};
	std::thread t3{[&]{queue.push(value);}};
	std::thread t4{[&]{queue.pop();}};
	std::thread t5{[&]{queue.pop();}};
	std::thread t6{[&]{queue.pop();}};
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	ASSERT_EQUAL(0,queue.size());
}

void test_multiple_threads_push_while_multiple_threads_call_pop_on_full_queue(){
	BoundedQueue<int> queue{5};
	int value{3};
	for(int i = 0; i<5;i++){
		queue.push(value);
	}
	std::thread t1{[&]{queue.push(value);}};
	std::thread t2{[&]{queue.push(value);}};
	std::thread t3{[&]{queue.push(value);}};
	std::thread t4{[&]{queue.pop();}};
	std::thread t5{[&]{queue.pop();}};
	std::thread t6{[&]{queue.pop();}};
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	ASSERT_EQUAL(5,queue.size());
}

cute::suite make_suite_bounded_queue_student_suite(){
	cute::suite s;
	s.push_back(CUTE(test_one_thread_calling_push_or_pop));
	s.push_back(CUTE(test_one_thread_calls_push_other_thread_calls_pop));
	s.push_back(CUTE(test_multiple_threads_calling_push_on_empty_queue));
	s.push_back(CUTE(test_multiple_threads_calling_push_on_full_queue));
	s.push_back(CUTE(test_multiple_threads_calling_pop_on_empty_queue));
	s.push_back(CUTE(test_multiple_threads_calling_pop_on_full_queue));
	s.push_back(CUTE(test_multiple_threads_calling_pop_on_partially_full_queue_with_insufficent_items));
	s.push_back(CUTE(test_multiple_threads_calling_push_while_one_calls_pop_on_empty_queue));
	s.push_back(CUTE(test_multiple_threads_calling_push_while_one_calls_pop_on_full_queue));
	s.push_back(CUTE(test_multiple_threads_push_while_multiple_threads_call_pop_on_empty_queue));
	s.push_back(CUTE(test_multiple_threads_push_while_multiple_threads_call_pop_on_full_queue));
	return s;
}


