#ifndef BOUNDEDBUFFER_H_
#define BOUNDEDBUFFER_H_

#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <boost/operators.hpp>

template<typename T>
class BoundedBuffer{
	unsigned int head_{0};
	unsigned int elements_{0};
	char * dynamic_container_ = nullptr;
	unsigned int dynamic_container_size_{0};

public:
	using size_type =  std::size_t;
	using value_type = T;
	using const_reference = T const &;
	using reference = T &;

	template<typename TYPE = value_type>
	struct iter:boost::random_access_iterator_helper<iter<TYPE>,TYPE>{
		using difference_type = typename iter::difference_type;
		BoundedBuffer const & buffer;
		size_type index;

		explicit iter(BoundedBuffer const & input_buff, size_type input_index):buffer{input_buff},index{input_index}{}

	private:
		void check_if_buffers_same(iter const & rhs) const{
			if(buffer.dynamic_container_ != rhs.buffer.dynamic_container_)
				throw std::logic_error{"Relative comparison on different buffers not possible"};
		}

	public:
		value_type & operator[](int iter_index)const{
			return buffer[buffer.head_+iter_index];
		}

		value_type & operator=(const iter & rhs){
			buffer = rhs.buffer;
			index = rhs.index;
			return *this;
		}

		value_type & operator*()const{
			if(index == buffer.elements_) throw std::logic_error{"Can't access element at end"};
			return buffer[index];
		}

		iter & operator++(){
			if(index == buffer.elements_) throw std::logic_error{"Can't increment over end"};
			index = (index + 1)%(buffer.capacity()+1);
			return *this;
		}

		iter & operator+(size_type distance){
			for(unsigned int i = 0; i < distance;i++){
				++(*this);
			}
			return *this;
		}

		iter & operator--(){
			if(index == 0) throw std::logic_error{"Can't decreement below begin"};
			index = index == 0?buffer.capacity():index -1;
			return *this;
		}

		iter & operator-(size_type distance){
			for(unsigned int i = 0; i < distance;i++){
				--(*this);
			}
			return *this;
		}

		difference_type operator-(iter const & rhs){
			check_if_buffers_same(rhs);
			difference_type diff{0};
			iter internal = rhs;
			while(index != internal.index){
				diff++;
				internal++;
			}
			return diff;
		}

		iter & operator+=(size_type distance){

			return *this + distance;
		}

		iter & operator-=(size_type distance){
			return *this - distance;
		}

		bool operator==(const iter & rhs) const{
			check_if_buffers_same(rhs);
			return index == rhs.index;
		}

		bool operator<(const iter & rhs) const{
			check_if_buffers_same(rhs);
			return index < rhs.index;
		}

		value_type * operator->() const{
			return reinterpret_cast<value_type *>(buffer.dynamic_container_);
		}

	};

	using iterator = iter<>;
	using const_iterator = iter<const value_type>;

public:
	void clear(){
		while(!empty()){
			pop();
		}
		head_ = 0;
	}

	BoundedBuffer():head_{0},elements_{0},dynamic_container_{nullptr},
			dynamic_container_size_{0}{}

	~BoundedBuffer()
	{
		while(!empty()){
			pop();
		}
		delete[] dynamic_container_;
	}

	BoundedBuffer(int const buffer_size):head_{0},elements_{0}{
		if(buffer_size <= 0) throw std::invalid_argument{"Capacity of BoundedBuffer can't be zero"};
		dynamic_container_size_ = buffer_size;
		dynamic_container_ = new char[(dynamic_container_size_)*sizeof(T)];
	}

	BoundedBuffer(BoundedBuffer const & elem){
		dynamic_container_ = new char[(elem.capacity())*sizeof(T)];
		dynamic_container_size_ = elem.dynamic_container_size_;
		auto elembuffer=reinterpret_cast<value_type*>(elem.dynamic_container_);
		if(elem.size()>0){
			size_t index_in_elem_buffer = &elem.front()-elembuffer;
			for(unsigned int i = 0; i < elem.size();i++){
				push(elembuffer[index_in_elem_buffer++]);
				if (index_in_elem_buffer>=elem.capacity())index_in_elem_buffer=0;
			}
		}
	}

	BoundedBuffer(BoundedBuffer && elem){
		if (this != &elem){
			clear();
			if(size() != elem.size()){
				delete [] dynamic_container_;
				dynamic_container_=nullptr;
				dynamic_container_size_=0;
			}
			swap(elem);
		}
	}

	BoundedBuffer & operator=(BoundedBuffer const & elem){
		//TODO: Nach Anpassung des Iterators kann hier auch optimiert werden
		if(this != &elem){
			if(size() > 0){
				clear();
			}
			if(capacity() != elem.capacity()){
				if(dynamic_container_){
					delete[] dynamic_container_;
				}
				dynamic_container_ = new char[(elem.capacity())*sizeof(T)];
				dynamic_container_size_ = elem.dynamic_container_size_;
			}
			auto elembuffer=reinterpret_cast<value_type*>(elem.dynamic_container_);
			if(elem.size()>0){
				size_t index_in_elem_buffer = &elem.front()-elembuffer;
				for(unsigned int i = 0; i < elem.size();i++){
					push(elembuffer[index_in_elem_buffer++]);
					if (index_in_elem_buffer>=elem.capacity())index_in_elem_buffer=0;
				}
			}
		}
		return *this;
	}

	BoundedBuffer & operator=(BoundedBuffer && elem){
		if (this != &elem){
			clear();
			if(size() != elem.size()){
				delete [] dynamic_container_;
				dynamic_container_=nullptr;
				dynamic_container_size_=0;
			}
			swap(elem);
		}
		return *this;
	}

	value_type & operator[](int index) const{
		int limit = capacity();
		if(index >= limit || index <= -limit) throw std::out_of_range{"Out of bounds access"};
		value_type * container = reinterpret_cast<value_type *>(dynamic_container_);
		int access_index{0};
		if(index >= 0 && index < limit){access_index = (head_+index)%capacity();}
		if(index < 0 && index > -limit){access_index = capacity() + index;}
		return container[access_index];
	}

	bool empty() const{
		return elements_ == 0;
	}

	size_type size() const{
		return elements_;
	}

	size_type capacity() const{
		return dynamic_container_size_;
	}

	unsigned int tail() const{
		return (head_ + elements_)%capacity();
	}


	bool full() const{
		return elements_ == capacity();
	};

	reference front(){
		if(empty()) throw std::logic_error{"Invalid use of front on empty BoundedBuffer"};
		return *(reinterpret_cast<value_type*>(dynamic_container_+(head_*sizeof(value_type))));
	}

	const_reference front() const{
		if(empty()) throw std::logic_error{"Invalid use of front on empty BoundedBuffer"};
		return *(reinterpret_cast<value_type*>(dynamic_container_+(head_*sizeof(value_type))));
	}

	reference back(){
		if(empty()) throw std::logic_error{"Invalid use of back on empty BoundedBuffer"};
	    int back_tail_ = tail() == 0? capacity()-1:tail()-1;
		return *(reinterpret_cast<value_type*>(dynamic_container_+(back_tail_*sizeof(value_type))));
	}

	const_reference back() const{
		if(empty()) throw std::logic_error{"Invalid use of back on empty BoundedBuffer"};
		int back_tail_ = tail() == 0? capacity()-1:tail()-1;
		return *(reinterpret_cast<value_type*>((dynamic_container_+(back_tail_*sizeof(value_type)))));
	}

	void push(value_type const & elem){
		if(full()) throw std::logic_error{"Invalid use of push on full BoundedBuffer"};
		auto pointer = reinterpret_cast<value_type*>(dynamic_container_ +(tail()*sizeof(value_type)));
		new (pointer) value_type{elem};
		elements_++;
	}

	void push(value_type && elem){
		if(full()) throw std::logic_error{"Invalid use of push on full BoundedBuffer"};
		auto pointer = reinterpret_cast<value_type*>(dynamic_container_ +(tail()*sizeof(value_type)));
		new (pointer) value_type{std::move(elem)};
		elements_++;
	}

	void pop(){
		if(empty()) throw std::logic_error{"Invalid use of pop on empty BoundedBuffer"};
		value_type* pointer = reinterpret_cast<value_type*>(dynamic_container_ + (head_*sizeof(value_type)));
		pointer->~T();
		head_ = (head_+1)%(capacity());
		elements_--;
	}

	void swap(BoundedBuffer & elem){
		std::swap(dynamic_container_,elem.dynamic_container_);
		std::swap(head_,elem.head_);
		std::swap(elements_,elem.elements_);
		std::swap(dynamic_container_size_,elem.dynamic_container_size_);
	}

	void push_many(){

	}

	template<typename FIRST, typename...REST>
	void push_many(FIRST && first, REST&&...rest) {
	  push(std::forward<FIRST>(first));
	  push_many(std::forward<decltype(rest)>(rest)...);
	}

	template<typename...TYPE>
	static BoundedBuffer<value_type> make_buffer(const int size, TYPE&&...param){
		int const number_of_arguments = sizeof...(TYPE);
		if(number_of_arguments > size)throw std::invalid_argument{"Invalid argument"};
		BoundedBuffer<value_type> buffer{size};
		buffer.push_many(std::forward<TYPE>(param)...);
		return buffer;
	}

	iterator begin(){
		return iterator{*this,0};
	}

	iterator end(){
		return iterator{*this,elements_};
	}

	const_iterator begin() const{
		return const_iterator{*this,0};
	}

	const_iterator end() const{
		return const_iterator{*this,elements_};
	}

	const_iterator const cbegin()const{
		return begin();
	}

	const_iterator const cend()const{
		return end();
	}
};


#endif /* BOUNDEDBUFFER_H_ */
