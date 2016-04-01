#ifndef BOUNDEDBUFFER_H_
#define BOUNDEDBUFFER_H_
#include <array>
#include <stdexcept>
#include <algorithm>

template<typename T>
class BoundedBuffer{
	unsigned int elements{0};
	unsigned int index{0};
	T * dynamic_container;
	unsigned int dynamic_container_size = 10;

	bool index_is_over_buffer_size() const {
		return index > dynamic_container_size;
	}

	void pre_push_operation() const{
		if(full()) throw std::logic_error{"Buffer is full"};
	};

	void post_push_operation(){
		if(!index_is_over_buffer_size()){
			elements++;
		}
		index++;
	};

public:
	using size_type =  std::size_t;
	using value_type = T;
	using const_reference = T const &;
	using reference = T &;


	BoundedBuffer(){
		dynamic_container = new T[dynamic_container_size]{};
	}
	~BoundedBuffer(){
		delete[] dynamic_container;
	}

	BoundedBuffer(int const buffer_size){
		dynamic_container_size = buffer_size;
		dynamic_container = new T[buffer_size]{};
	}

	BoundedBuffer(BoundedBuffer const & elem):elements{elem.elements},index{elem.index},
			dynamic_container_size{elem.dynamic_container_size}{
		dynamic_container = new T[dynamic_container_size]{};
		std::copy(elem.dynamic_container,elem.dynamic_container+elem.dynamic_container_size,dynamic_container);
	}

	BoundedBuffer(BoundedBuffer && elem):elements{std::move(elem.elements)},index{std::move(elem.index)},
			dynamic_container_size{std::move(elem.dynamic_container_size)}{
		dynamic_container = std::addressof(elem.dynamic_container);
		elem.dynamic_container = nullptr;
	}

	BoundedBuffer & operator=(BoundedBuffer const & elem){
		dynamic_container = new T[elem.dynamic_container_size]{};
		std::copy(elem.dynamic_container,elem.dynamic_container+elem.dynamic_container_size,dynamic_container);
		elements = elem.elements;
		index = elem.index;
		return *this;
	}

	BoundedBuffer & operator=(BoundedBuffer && elem){
		dynamic_container_size = std::move(elem.dynamic_container_size);
		dynamic_container = std::addressof(elem.dynamic_container);
		elem.dynamic_container = nullptr;
		elements = std::move(elem.elements);
		index = std::move(elem.index);
		return *this;
	}

	bool empty() const{
		return elements < 1;
	};

	bool full() const{
		return elements == dynamic_container_size;
	};
	size_type size() const{
		return elements;
	}

	size_type capacity() const{
		return dynamic_container_size;
	}

	reference front(){
		if(empty()) throw std::logic_error{"BoundedBuffer is empty"};
		return dynamic_container[0];
	};
	const_reference front() const{
		if(empty()) throw std::logic_error{"BoundedBuffer is empty"};
		return dynamic_container[0];
	};

	reference back(){
		if(empty()) throw std::logic_error{"BoundedBuffer is empty"};
		return dynamic_container[((index-1)%dynamic_container_size)];
	};

	const_reference back() const{
		if(empty()) throw std::logic_error{"BoundedBuffer is empty"};
		return dynamic_container[((index-1)%dynamic_container_size)];
	};

	void push(value_type const & elem){
		pre_push_operation();
		dynamic_container[(index%dynamic_container_size)] = elem;
		post_push_operation();
	};

	void push(value_type && elem){
		pre_push_operation();
		dynamic_container[(index%dynamic_container_size)] = std::move(elem);
		post_push_operation();
	};

	void pop(){
		if(empty()) throw std::logic_error{"BoundedBuffer is empty"};

		for(unsigned int i = 0; i <dynamic_container_size-1;i++){
			dynamic_container[i] = dynamic_container[i+1];
		}

		if(!index_is_over_buffer_size()){
			elements--;
		}
		index--;
	};

	void swap(BoundedBuffer & elem){
		std::swap(dynamic_container,elem.dynamic_container);
		std::swap(elements,elem.elements);
		std::swap(index,elem.index);
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
