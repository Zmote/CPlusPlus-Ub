#ifndef BOUNDEDBUFFER_H_
#define BOUNDEDBUFFER_H_

#include <stdexcept>
#include <iterator>
#include <memory>
#include <algorithm>
#include <type_traits>

//TODO: implement iterator logic --> proper implementation of iterator ops outstanding
//TODO: Minor fix of destructor op, 2x instead of 1x

template<typename T>
class BoundedBuffer{
	unsigned int head_{0};
	unsigned int tail_{0};
	unsigned int elements_{0};
	char * dynamic_container_ = nullptr;
	unsigned int dynamic_container_size_{0};

public:
	using size_type =  std::size_t;
	using value_type = T;
	using const_reference = T const &;
	using reference = T &;

	struct iterator:std::iterator<std::random_access_iterator_tag,BoundedBuffer>{
		using difference_type = typename iterator::difference_type;
		value_type* value;
		value_type* start;
		value_type* end;
		char * dynamic_container_;
		unsigned int dynamic_container_size_;
		explicit iterator(value_type* start,value_type* end, char * dynamic_c, unsigned int dynamic_c_s)
		:value{start},start{start},end{end},dynamic_container_{dynamic_c},dynamic_container_size_{dynamic_c_s}{}

		reference & operator*()const{
			return *value;
		}

		value_type* operator->() const{
			return value;
		}

		bool operator==(iterator const & it) const{return value == it.value;}
		bool operator!=(iterator const & it) const{return !(*this == it);}
		bool operator<(iterator const & it)const{return value < it.value;}
		bool operator>(iterator const & it)const{return value > it.value;}

		reference operator[](int index){

		}

		iterator & operator--(){
			auto buffer = reinterpret_cast<value_type*>(dynamic_container_);
			int currentIndex = value - buffer;
			int previousIndex = currentIndex-1 < 0?dynamic_container_size_-1:currentIndex-1;
			value = reinterpret_cast<value_type*>(dynamic_container_+(previousIndex));
			return *this;
		}

		iterator & operator--(int){
			auto old = *this;
			--(*this);
			return old;
		}
		iterator & operator-(int const & count){

		}
		difference_type & operator-(iterator const & it){

		}

		iterator & operator-=(int const & count){

		}

		difference_type & operator-=(iterator const & it){

		}

		iterator & operator++(){
			auto buffer = reinterpret_cast<value_type*>(dynamic_container_);
			int currentIndex = value - buffer;
			value = reinterpret_cast<value_type*>(dynamic_container_+(((currentIndex+1)%dynamic_container_size_)*sizeof(T)));
			if(value == end) throw std::logic_error{"Iterator over end"};
			return *this;
		}

		iterator & operator++(int){
			auto old = *this;
			++(*this);
			return old;
		}

		iterator & operator+(int const & count){
			for(int i = 0; i < count;i++){
				++(*this);
			}
			return *this;
		}

		difference_type & operator+(iterator const & it){

		}
		iterator & operator+=(int const & count){
			return *this + count;
		}

		difference_type & operator+=(iterator const & it){

		}
	};

	struct const_iterator:std::iterator<std::random_access_iterator_tag,BoundedBuffer>{
		using difference_type = typename iterator::difference_type;
		value_type const * value;
		value_type const * start;
		value_type const * end;
		char * dynamic_container_;
		unsigned int dynamic_container_size_;
		explicit const_iterator(value_type const * start, value_type const * end, char * dynamic_c, unsigned int dynamic_c_s)
		:value{start}, start{start},end{end},dynamic_container_{dynamic_c},dynamic_container_size_{dynamic_c_s}{}

		const_reference operator*()const{return *value;}

		value_type* operator->() const{
			return value;
		}

		bool operator==(const_iterator const & it) const{return value == it.value;}
		bool operator!=(const_iterator const & it) const{return !(*this == it);}
		bool operator<(const_iterator const & it)const{return value < it.value;}
		bool operator>(const_iterator const & it)const{return value > it.value;}

		const_reference operator[](int index){

		}

		const_iterator & operator--(){
			auto buffer = reinterpret_cast<value_type*>(dynamic_container_);
			int currentIndex = value - buffer;
			int previousIndex = currentIndex-1 < 0?dynamic_container_size_-1:currentIndex-1;
			value = reinterpret_cast<value_type*>(dynamic_container_+(previousIndex));
			return *this;
		}

		const_iterator & operator--(int){
			auto old = *this;
			--(*this);
			return old;
		}
		const_iterator & operator-(int const & count){

		}

		difference_type & operator-(const_iterator const & cit){

		}

		const_iterator & operator-=(int const & count){

		}

		difference_type & operator-=(const_iterator const & cit){

		}

		const_iterator & operator++(){
			auto buffer = reinterpret_cast<value_type*>(dynamic_container_);
			int currentIndex = value - buffer;
			value = reinterpret_cast<value_type*>(dynamic_container_+(((currentIndex+1)%dynamic_container_size_)*sizeof(T)));

			return *this;
		}

		const_iterator & operator++(int){
			auto old = *this;
			++(*this);
			return old;
		}

		const_iterator & operator+(int const & count){

		}
		difference_type & operator+(const_iterator const & cit){

		}

		const_iterator & operator+=(int const & count){

		}
		difference_type & operator+=(const_iterator const & cit){

		}
	};

	void clear(){
		while(!empty()){
			pop();
		}
		head_ = 0;
		tail_ = 0;
	}

	BoundedBuffer():head_{0},tail_{0},elements_{0},dynamic_container_{nullptr},
			dynamic_container_size_{0}{}

	~BoundedBuffer()
	{
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

	BoundedBuffer(BoundedBuffer const & elem){
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
	}

	BoundedBuffer(BoundedBuffer && elem):head_{std::move(elem.head_)},tail_{std::move(elem.tail_)},
			elements_{std::move(elem.elements_)},dynamic_container_{std::move(elem.dynamic_container_)},
			dynamic_container_size_{std::move(elem.dynamic_container_size_)}{
				elem.dynamic_container_ = nullptr;
	}

	BoundedBuffer & operator=(BoundedBuffer const & elem){
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

	bool empty() const{
		return elements_ == 0;
	}

	size_type size() const{
		return elements_;
	}

	size_type capacity() const{
		return dynamic_container_size_;
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
		int back_tail_ = tail_ == 0? capacity()-1:tail_-1;
		return *(reinterpret_cast<value_type*>(dynamic_container_+(back_tail_*sizeof(value_type))));
	}

	const_reference back() const{
		if(empty()) throw std::logic_error{"Invalid use of back on empty BoundedBuffer"};
		int back_tail_ = tail_ == 0? capacity()-1:tail_-1;
		return *(reinterpret_cast<value_type*>((dynamic_container_+(back_tail_*sizeof(value_type)))));
	}

	void push(value_type const & elem){
		if(full()) throw std::logic_error{"Invalid use of push on full BoundedBuffer"};
		auto pointer = reinterpret_cast<value_type*>(dynamic_container_ +(tail_*sizeof(value_type)));
		new (pointer) value_type{elem};
		tail_ = (tail_+1)%capacity();
		elements_++;
	}

	void push(value_type && elem){
		if(full()) throw std::logic_error{"Invalid use of push on full BoundedBuffer"};
		auto pointer = reinterpret_cast<value_type*>(dynamic_container_ +(tail_*sizeof(value_type)));
		new (pointer) value_type{std::move(elem)};
		tail_ = (tail_+1)%capacity();
		elements_++;
	}

	void pop(){
		if(empty()) throw std::logic_error{"Invalid use of pop on empty BoundedBuffer"};
		value_type* pointer = reinterpret_cast<value_type*>(dynamic_container_ + (head_*sizeof(value_type)));
		pointer->~T();
		head_ = (head_+1)%capacity();
		elements_--;
	}

	void swap(BoundedBuffer & elem){
		std::swap(dynamic_container_,elem.dynamic_container_);
		std::swap(head_,elem.head_);
		std::swap(tail_,elem.tail_);
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
		value_type* pointer_to_start = reinterpret_cast<value_type*>(dynamic_container_);
		value_type* pointer_to_end = reinterpret_cast<value_type*>(dynamic_container_);
		if(size() > 0){
			auto buffer = reinterpret_cast<value_type*>(dynamic_container_);
			size_t index_of_front = &front() - buffer;
			size_t index_of_back = &back() - buffer;
			pointer_to_start = reinterpret_cast<value_type*>(dynamic_container_+(index_of_front*sizeof(T)));
			pointer_to_end = reinterpret_cast<value_type*>(dynamic_container_+(index_of_back*sizeof(T)));
		}
		return iterator{pointer_to_start, pointer_to_end,dynamic_container_,dynamic_container_size_};
	}

	iterator end(){
		value_type* pointer_to_start = reinterpret_cast<value_type*>(dynamic_container_);
		value_type* pointer_to_end = reinterpret_cast<value_type*>(dynamic_container_);
		if(size() > 0){
			auto buffer = reinterpret_cast<value_type*>(dynamic_container_);
			size_t index_of_front = &front() - buffer;
			size_t index_of_back = &back() - buffer;
			pointer_to_start = reinterpret_cast<value_type*>(dynamic_container_+(index_of_front*sizeof(T)));
			pointer_to_end = reinterpret_cast<value_type*>(dynamic_container_+(index_of_back*sizeof(T)));
		}
		return iterator{pointer_to_start, pointer_to_end,dynamic_container_,dynamic_container_size_};
	}

	const_iterator begin() const{
		value_type const * pointer_to_start = reinterpret_cast<value_type const *>(dynamic_container_);
		value_type const * pointer_to_end = reinterpret_cast<value_type*>(dynamic_container_);
		if(size()>0){
			pointer_to_start = &front();
			pointer_to_end = &back();
		}
		return const_iterator{pointer_to_start,pointer_to_end,dynamic_container_,dynamic_container_size_};
	}

	const_iterator end() const{
		value_type const * pointer_to_start = reinterpret_cast<value_type const *>(dynamic_container_);
		value_type const * pointer_to_end = reinterpret_cast<value_type const *>(dynamic_container_);
		if(size()>0){
			pointer_to_start = &front();
			pointer_to_end = &back();
		}
		return const_iterator{pointer_to_start, pointer_to_end,dynamic_container_,dynamic_container_size_};
	}

	const_iterator cbegin()const{
		value_type const * pointer_to_start = reinterpret_cast<value_type const *>(dynamic_container_);
		value_type const * pointer_to_end = reinterpret_cast<value_type const *>(dynamic_container_);
		if(size()>0){
			pointer_to_start = &front();
			pointer_to_end = &back();
		}
		return const_iterator{pointer_to_start, pointer_to_end,dynamic_container_,dynamic_container_size_};
	}

	const_iterator cend()const{
		value_type const * pointer_to_start = reinterpret_cast<value_type const *>(dynamic_container_);
		value_type const * pointer_to_end = reinterpret_cast<value_type const *>(dynamic_container_);
		if(size()>0){
			pointer_to_start = &front();
			pointer_to_end = &back();
		}
		return const_iterator{pointer_to_start,pointer_to_end,dynamic_container_,dynamic_container_size_};
	}


};


#endif /* BOUNDEDBUFFER_H_ */
