#ifndef BOUNDEDBUFFER_H_
#define BOUNDEDBUFFER_H_
#include <array>
#include <stdexcept>
#include <algorithm>

template<typename T, std::size_t SIZET>
class BoundedBuffer{
	using container_type = std::array<T,SIZET>;
	container_type myContainer;
	unsigned int elements_{0};
	unsigned int tail_{0};

	bool index_is_over_buffer_size() const {
		return tail_ > myContainer.size();
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
	using size_type =  typename container_type::size_type;
	using value_type = typename container_type::value_type;
	using const_reference = typename container_type::const_reference;
	using reference = typename container_type::reference;

	BoundedBuffer() = default;
	BoundedBuffer(BoundedBuffer const & elem):myContainer{elem.myContainer},
			elements_{elem.elements_},tail_{elem.tail_}{};
	BoundedBuffer(BoundedBuffer && elem):myContainer{std::move(elem.myContainer)},
			elements_{std::move(elem.elements_)},tail_{std::move(elem.tail_)}{};

	BoundedBuffer & operator=(BoundedBuffer const & elem){
		myContainer = elem.myContainer;
		elements_ = elem.elements_;
		tail_ = elem.tail_;
		return *this;
	}

	BoundedBuffer & operator=(BoundedBuffer && elem){
		myContainer = std::move(elem.myContainer);
		elements_ = std::move(elem.elements_);
		tail_ = std::move(elem.tail_);
		return *this;
	}

	bool empty() const{
		return elements_ < 1;
	};

	bool full() const{
		return elements_ == myContainer.size();
	};
	size_type size() const{
		return elements_;
	}

	reference front(){
		if(empty()) throw std::logic_error{"BoundedBuffer is empty"};
		return myContainer.at(0);
	};
	const_reference front() const{
		if(empty()) throw std::logic_error{"BoundedBuffer is empty"};
		return myContainer.at(0);
	};

	reference back(){
		if(empty()) throw std::logic_error{"BoundedBuffer is empty"};
		return myContainer.at((tail_-1)%myContainer.size());
	};

	const_reference back() const{
		if(empty()) throw std::logic_error{"BoundedBuffer is empty"};
		return myContainer.at((tail_-1)%myContainer.size());
	};

	void push(value_type const & elem){
		pre_push_operation();
		myContainer.at(tail_%myContainer.size()) = elem;
		post_push_operation();
	};

	void push(value_type && elem){
		pre_push_operation();
		myContainer.at(tail_%myContainer.size()) = std::move(elem);
		post_push_operation();
	};

	void pop(){
		if(empty()) throw std::logic_error{"BoundedBuffer is empty"};

		for(unsigned int i = 0; i < myContainer.size()-1;i++){
			myContainer.at(i) = myContainer.at(i+1);
		}

		if(!index_is_over_buffer_size()){
			elements_--;
		}
		tail_--;
	};

	void swap(BoundedBuffer & elem){

		BoundedBuffer swap_store_buffer{};

		std::copy(elem.myContainer.begin(),elem.myContainer.end(),swap_store_buffer.myContainer.begin());
		std::copy(myContainer.begin(),myContainer.end(),elem.myContainer.begin());
		std::copy(swap_store_buffer.myContainer.begin(),swap_store_buffer.myContainer.end(),myContainer.begin());

		swap_store_buffer.elements_ = elements_;
		swap_store_buffer.tail_ = tail_;
		elements_ = elem.elements_;
		tail_ = elem.tail_;
		elem.elements_ = swap_store_buffer.elements_;
		elem.tail_ = swap_store_buffer.tail_;
	};

//	static BoundedBuffer<T,SIZET> make_buffer(T && param){
//		BoundedBuffer<T,SIZET> buffer{};
//		buffer.push(std::forward<T>(param));
//		return buffer;
//	};
};


#endif /* BOUNDEDBUFFER_H_ */
