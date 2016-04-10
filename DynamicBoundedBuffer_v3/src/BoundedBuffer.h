#ifndef BOUNDEDBUFFER_H_
#define BOUNDEDBUFFER_H_
#include <array>
#include <stdexcept>
#include <algorithm>
#include <type_traits>

//TODO: the idea of the "RingBuffer" is that it should automatically overwrite  objects if index out of "capacity" scope
// see if you can find a solutation which requires no "index_is_over_buffer_size()" implementation
template<typename T>
class BoundedBuffer{
	unsigned int head_;
	unsigned int tail_;
	unsigned int elements_;
	void * dynamic_container_;
	unsigned int dynamic_container_size_ = 10;

public:
	using size_type =  std::size_t;
	using value_type = T;
	using const_reference = T const &;
	using reference = T &;


	BoundedBuffer():head_{0},tail_{0},elements_{0}{
		dynamic_container_ = new unsigned char[dynamic_container_size_*sizeof(T)];
	}
	~BoundedBuffer(){
		delete[] (T*)dynamic_container_;
	}

	BoundedBuffer(int const buffer_size):BoundedBuffer(){
		if(buffer_size <= 0) throw std::invalid_argument{"Capacity of BoundedBuffer can't be zero"};
		dynamic_container_size_ = buffer_size;
	}

	BoundedBuffer(BoundedBuffer const & elem):head_{elem.head_},tail_{elem.tail_},
			elements_{elem.elements_}{
		dynamic_container_ = new unsigned char[dynamic_container_size_*sizeof(T)];
		dynamic_container_size_ = elem.dynamic_container_size_;
		std::copy((T*)elem.dynamic_container_,((T*)dynamic_container_)+dynamic_container_size_,(T*)dynamic_container_);
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
		dynamic_container_ = new unsigned char[dynamic_container_size_*sizeof(T)];
		std::copy((T*)elem.dynamic_container_,((T*)dynamic_container_)+dynamic_container_size_,(T*)dynamic_container_);
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
		return *((T*)dynamic_container_+head_);
	}

	const_reference front() const{
		if(empty()) throw std::logic_error{"Invalid use of front on empty BoundedBuffer"};
		return *((T*)dynamic_container_+head_);
	}

	reference back(){
		if(empty()) throw std::logic_error{"Invalid use of back on empty BoundedBuffer"};
		return *((T*)dynamic_container_+tail_);
	}

	const_reference back() const{
		if(empty()) throw std::logic_error{"Invalid use of back on empty BoundedBuffer"};
		return *((T*)dynamic_container_+tail_);
	}

	void push(value_type const & elem){
		if(full()) throw std::logic_error{"Invalid use of push on full BoundedBuffer"};
		new (((T*)(dynamic_container_))+tail_) T{elem};
		tail_ = (tail_+1)%dynamic_container_size_;
		elements_++;
	}

	void push(value_type && elem){
		if(full()) throw std::logic_error{"Invalid use of push on full BoundedBuffer"};
		new (((T*)(dynamic_container_))+tail_) T{std::move(elem)};
		tail_ = (tail_+1)%dynamic_container_size_;
		elements_++;
	}

	void pop(){
		if(empty()) throw std::logic_error{"Invalid use of pop on empty BoundedBuffer"};
		head_ = (tail_+(dynamic_container_size_-elements_))%dynamic_container_size_;

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
