#ifndef BOUNDEDBUFFER_H_
#define BOUNDEDBUFFER_H_
#include <array>
#include <stdexcept>
#include <algorithm>
#include <type_traits>

//TODO: Heap error fixed, but now it's pushing weird values, check out why
template<typename T>
class BoundedBuffer{
	unsigned int head_;
	unsigned int tail_;
	unsigned int elements_;
	char * dynamic_container_;
	unsigned int dynamic_container_size_ = 10;

public:
	using size_type =  std::size_t;
	using value_type = T;
	using const_reference = T const &;
	using reference = T &;


	BoundedBuffer():head_{0},tail_{0},elements_{0}{
		dynamic_container_ = new char[(dynamic_container_size_)*sizeof(T)];
	}
	~BoundedBuffer(){
		while(!empty()){
			pop();
		}
		delete[] dynamic_container_;
	}

	BoundedBuffer(int const buffer_size):head_{0},tail_{0},elements_{0}{
		if(buffer_size <= 0) throw std::invalid_argument{"Capacity of BoundedBuffer can't be zero"};
		dynamic_container_size_ = buffer_size;
		dynamic_container_ = new char[(dynamic_container_size_)*sizeof(T)];
	}

	BoundedBuffer(BoundedBuffer const & elem):head_{elem.head_},tail_{elem.tail_},
			elements_{elem.elements_}{
		dynamic_container_size_ = elem.dynamic_container_size_;
		dynamic_container_ = new char[(dynamic_container_size_)*sizeof(T)];
		std::copy(elem.dynamic_container_,(dynamic_container_)+dynamic_container_size_,dynamic_container_);
	}

	BoundedBuffer(BoundedBuffer && elem):head_{std::move(elem.head_)},tail_{std::move(elem.tail_)},
			elements_{std::move(elem.elements_)},dynamic_container_{std::move(elem.dynamic_container_)},
			dynamic_container_size_{std::move(elem.dynamic_container_size_)}{
				elem.dynamic_container_ = nullptr;
	}

	BoundedBuffer & operator=(BoundedBuffer const & elem){
		head_ = elem.head_;
		tail_ = elem.tail_;
		elements_ = elem.elements_;
		dynamic_container_size_ = elem.dynamic_container_size_;
		dynamic_container_ = new char[(dynamic_container_size_)*sizeof(T)];
		std::copy(elem.dynamic_container_,(dynamic_container_)+dynamic_container_size_,dynamic_container_);
		return *this;
	}

	BoundedBuffer & operator=(BoundedBuffer && elem){
		head_ = std::move(elem.head_);
		tail_ = std::move(elem.tail_);
		elements_ = std::move(elem.elements_);
		dynamic_container_size_ = std::move(elem.dynamic_container_size_);
		dynamic_container_ = elem.dynamic_container_;
		elem.dynamic_container_ = nullptr;
		return *this;
	}

	bool empty() const{
		return elements_ == 0;
	}

	bool full() const{
		return elements_ == dynamic_container_size_;
	};
	size_type size() const{
		return elements_;
	}

	size_type capacity() const{
		return dynamic_container_size_;
	}

	reference front(){
		if(empty()) throw std::logic_error{"Invalid use of front on empty BoundedBuffer"};
		return *((T*)(dynamic_container_+head_));
	}

	const_reference front() const{
		if(empty()) throw std::logic_error{"Invalid use of front on empty BoundedBuffer"};
		return *((T*)(dynamic_container_+head_));
	}

	reference back(){
		if(empty()) throw std::logic_error{"Invalid use of back on empty BoundedBuffer"};
		int back_tail_ = (tail_-1) < 0? dynamic_container_size_ -1: tail_-1;
		return *((T*)(dynamic_container_+back_tail_));
	}

	const_reference back() const{
		if(empty()) throw std::logic_error{"Invalid use of back on empty BoundedBuffer"};
		int back_tail_ = (tail_-1) < 0? dynamic_container_size_ -1: tail_-1;
		return *((T*)(dynamic_container_+back_tail_));
	}

	void push(value_type const & elem){
		if(full()) throw std::logic_error{"Invalid use of push on full BoundedBuffer"};
		::new (dynamic_container_+tail_) T{elem};
		tail_ = (tail_+1)%dynamic_container_size_;
		elements_++;
	}

	void push(value_type && elem){
		if(full()) throw std::logic_error{"Invalid use of push on full BoundedBuffer"};
		::new (dynamic_container_+tail_) T{std::move(elem)};
		tail_ = (tail_+1)%dynamic_container_size_;
		elements_++;
	}

	void pop(){
		if(empty()) throw std::logic_error{"Invalid use of pop on empty BoundedBuffer"};
		T* pointer = (T*)(dynamic_container_ + head_);
		pointer->~T();
		head_ = (head_+1)%dynamic_container_size_;
		elements_--;
	}

	void swap(BoundedBuffer & elem){
		std::swap(dynamic_container_,elem.dynamic_container_);
	}

	void push_many(){

	}

	template<typename FIRST, typename...REST>
	void push_many(FIRST && first, REST&&...rest) {
	  push(std::forward<FIRST>(first));
	  push_many(std::forward<decltype(rest)>(rest)...);
	}

	template<typename...TYPE>
	static BoundedBuffer<T> make_buffer(const int size, TYPE&&...param){
		int const number_of_arguments = sizeof...(TYPE);
		if(number_of_arguments > size)throw std::invalid_argument{"Invalid argument"};
		BoundedBuffer<T> buffer{size};
		buffer.push_many(std::forward<TYPE>(param)...);
		return buffer;
	}
};


#endif /* BOUNDEDBUFFER_H_ */
