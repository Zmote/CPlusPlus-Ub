#ifndef BOUNDEDBUFFER_H_
#define BOUNDEDBUFFER_H_
#include <array>
#include <stdexcept>
#include <algorithm>

template<typename T>
class BoundedBuffer{
	unsigned int elements_{0};
	unsigned int tail_{0};
	T * dynamic_container_;
	unsigned int dynamic_container_size_ = 10;

	bool index_is_over_buffer_size() const {
		return tail_ > dynamic_container_size_;
	}

	void pre_push_operation() const{
		if(full()) throw std::logic_error{"Buffer is full"};
	};

	void post_push_operation(){
		if(!index_is_over_buffer_size()){
			elements_++;
		}
		tail_++;
	};

public:
	using size_type =  std::size_t;
	using value_type = T;
	using const_reference = T const &;
	using reference = T &;

	BoundedBuffer(){
		dynamic_container_ = new T[dynamic_container_size_]{};
	}
	~BoundedBuffer(){
		delete[] dynamic_container_;
	}

	BoundedBuffer(int const buffer_size){
		if(buffer_size == 0) throw std::invalid_argument{"Buffer size can't be zero"};
		dynamic_container_size_ = buffer_size;
		dynamic_container_ = new T[buffer_size]{};
	}

	BoundedBuffer(BoundedBuffer const & elem):elements_{elem.elements_},tail_{elem.tail_},
			dynamic_container_size_{elem.dynamic_container_size_}{
		dynamic_container_ = new T[dynamic_container_size_]{};
		std::copy(elem.dynamic_container_,elem.dynamic_container_+elem.elements_,dynamic_container_);
	}

	BoundedBuffer(BoundedBuffer && elem):elements_{std::move(elem.elements_)},tail_{std::move(elem.tail_)},
			dynamic_container_size_{std::move(elem.dynamic_container_size_)}{
		dynamic_container_ = elem.dynamic_container_;
		elem.dynamic_container_ = nullptr;
	}

	BoundedBuffer & operator=(BoundedBuffer const & elem){
		if(this != &elem){
			dynamic_container_size_ = elem.dynamic_container_size_;
			dynamic_container_ = new T[elem.dynamic_container_size_]{};
			std::copy(elem.dynamic_container_,elem.dynamic_container_+elem.elements_,dynamic_container_);
			elements_ = elem.elements_;
			tail_ = elem.tail_;
		}
		return *this;
	}

	BoundedBuffer & operator=(BoundedBuffer && elem){
		dynamic_container_size_ = std::move(elem.dynamic_container_size_);
		dynamic_container_ = elem.dynamic_container_;
		elem.dynamic_container_ = nullptr;
		elements_ = std::move(elem.elements_);
		tail_ = std::move(elem.tail_);
		return *this;
	}

	bool empty() const{
		return elements_ < 1;
	};

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
		if(empty()) throw std::logic_error{"BoundedBuffer is empty"};
		return dynamic_container_[0];
	};
	const_reference front() const{
		if(empty()) throw std::logic_error{"BoundedBuffer is empty"};
		return dynamic_container_[0];
	};

	reference back(){
		if(empty()) throw std::logic_error{"BoundedBuffer is empty"};
		return dynamic_container_[((tail_-1)%dynamic_container_size_)];
	};

	const_reference back() const{
		if(empty()) throw std::logic_error{"BoundedBuffer is empty"};
		return dynamic_container_[((tail_-1)%dynamic_container_size_)];
	};

	void push(value_type const & elem){
		pre_push_operation();
		dynamic_container_[(tail_%dynamic_container_size_)] = elem;
		post_push_operation();
	};

	void push(value_type && elem){
		pre_push_operation();
		dynamic_container_[(tail_%dynamic_container_size_)] = std::move(elem);
		post_push_operation();
	};

	void pop(){
		if(empty()) throw std::logic_error{"BoundedBuffer is empty"};

		for(unsigned int i = 0; i <dynamic_container_size_-1;i++){
			dynamic_container_[i] = std::move(dynamic_container_[i+1]);
		}

		if(!index_is_over_buffer_size()){
			elements_--;
		}
		tail_--;
	};

	void swap(BoundedBuffer & elem){
		std::swap(dynamic_container_,elem.dynamic_container_);
		std::swap(elements_,elem.elements_);
		std::swap(tail_,elem.tail_);
	};

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
	};
};


#endif /* BOUNDEDBUFFER_H_ */
