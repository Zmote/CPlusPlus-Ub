#ifndef BOUNDEDBUFFER_H_
#define BOUNDEDBUFFER_H_

#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <type_traits>

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
	using const_value_type = T const;
	using const_reference = T const &;
	using reference = T &;

	template<typename TYPE = value_type>
	struct iter:std::iterator<std::random_access_iterator_tag,BoundedBuffer>{
		using difference_type = typename iter::difference_type;
		using TYPE_pointer = TYPE *;
		TYPE_pointer value;
		TYPE_pointer start;
		TYPE_pointer end;
		char * dynamic_container_;
		unsigned int dynamic_container_size_;

		explicit iter(TYPE_pointer value,TYPE_pointer start,TYPE_pointer end, char * dynamic_c, unsigned int dynamic_c_s)
		:value{value},start{start},end{end},dynamic_container_{dynamic_c},dynamic_container_size_{dynamic_c_s}{}

		TYPE & operator*()const{
			if(value == end){
				throw std::logic_error{"Can't access elem at end"};
			}
			return *value;
		}

		TYPE_pointer operator->() const{
			return value;
		}
		void check_if_buffers_same(iter const & it) const{
			if(this->dynamic_container_ != it.dynamic_container_) throw std::logic_error{"Relative comparison on different buffers not possible"};
		}

		bool operator==(iter const & it) const{check_if_buffers_same(it);return value == it.value;}
		bool operator!=(iter const & it) const{check_if_buffers_same(it);return !(*this == it);}
		bool operator<(iter const & it)const{check_if_buffers_same(it);return value < it.value;}
		bool operator>(iter const & it)const{check_if_buffers_same(it);return value > it.value;}

		reference operator[](int index){
			auto buffer = reinterpret_cast<TYPE_pointer>(dynamic_container_);
			int currentIndex = value - buffer;
			int newIndex = (currentIndex+index)%(dynamic_container_size_+1);
			return *(buffer+newIndex);
		}

		iter & operator--(){
			if(value == start)throw std::logic_error{"Reached start, can't go below"};
			auto buffer = reinterpret_cast<TYPE_pointer>(dynamic_container_);
			int currentIndex = value - buffer;
			int previousIndex = currentIndex - 1 < 0? dynamic_container_size_+ 1:currentIndex -1;
			value = reinterpret_cast<TYPE_pointer>(dynamic_container_+(previousIndex*sizeof(T)));
			return *this;
		}

		iter operator--(int){
			auto old = *this;
			--(*this);
			return old;
		}

		iter & operator-(int const & count){
			for(int i = 0; i < count; i++){
				*this = --(*this);
			}
			return *this;
		}

		iter & operator-=(int const & count){
			return *this - count;
		}



		iter & operator++(){
			if(value == end) throw std::logic_error{"Iterator over end"};
			auto buffer = reinterpret_cast<TYPE_pointer>(dynamic_container_);
			int currentIndex = value - buffer;
			value = reinterpret_cast<TYPE_pointer>(dynamic_container_+(((currentIndex+1)%(dynamic_container_size_+1))*sizeof(T)));
			return *this;
		}

		iter operator++(int){
			auto old = *this;
			++(*this);
			return old;
		}

		iter & operator+(int const & count){
			for(int i = 0; i < count;i++){
				*this = ++(*this);
			}
			return *this;
		}

		iter & operator+=(int const & count){
			return *this + count;
		}

		difference_type operator-(iter const & it){
			iter internal{*this};
			difference_type difference{0};
			if(internal.value < it.value){
				internal = --(internal);
			}
			while(internal != it){
				internal = --(internal);
				difference++;
			}
			return difference;
		}

		difference_type operator-=(iter const & it){
			return (*this) - it;
		}
	};
	using iterator = iter<>;
	using const_iterator = iter<const_value_type>;

private:
	template<typename ITERTYPE = iterator, typename VALUETYPE = value_type>
	ITERTYPE init_iterator(bool start_iter) const{
		VALUETYPE * value_ptr = reinterpret_cast<VALUETYPE*>(dynamic_container_);
		VALUETYPE * start_ptr = reinterpret_cast<VALUETYPE*>(dynamic_container_);
		VALUETYPE * end_ptr = reinterpret_cast<VALUETYPE*>(dynamic_container_);
		if(!empty()){
			start_ptr = reinterpret_cast<VALUETYPE*>(dynamic_container_+(head_*sizeof(T)));
			end_ptr = reinterpret_cast<VALUETYPE*>(dynamic_container_+(tail_*sizeof(T)));
			value_ptr = start_ptr;
			if(!start_iter){
				value_ptr = end_ptr;
			}
		}
		return ITERTYPE{value_ptr,start_ptr,end_ptr,dynamic_container_,dynamic_container_size_};
	}

public:
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
		dynamic_container_ = new char[(dynamic_container_size_+1)*sizeof(T)];
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
				dynamic_container_ = new char[(elem.capacity()+1)*sizeof(T)];
				dynamic_container_size_ = elem.dynamic_container_size_;
			}
			auto elembuffer=reinterpret_cast<value_type*>(elem.dynamic_container_);
			if(elem.size()>0){
				size_t index_in_elem_buffer = &elem.front()-elembuffer;
				for(unsigned int i = 0; i < elem.size();i++){
					push(elembuffer[index_in_elem_buffer++]);
					if (index_in_elem_buffer>=elem.capacity()+1)index_in_elem_buffer=0;
				}
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
		if(this != &elem){
			if(size() > 0){
				clear();
			}
			if(capacity() != elem.capacity()){
				if(dynamic_container_){
					delete[] dynamic_container_;
				}
				dynamic_container_ = new char[(elem.capacity()+1)*sizeof(T)];
				dynamic_container_size_ = elem.dynamic_container_size_;
			}
			auto elembuffer=reinterpret_cast<value_type*>(elem.dynamic_container_);
			if(elem.size()>0){
				size_t index_in_elem_buffer = &elem.front()-elembuffer;
				for(unsigned int i = 0; i < elem.size();i++){
					push(elembuffer[index_in_elem_buffer++]);
					if (index_in_elem_buffer>=elem.capacity()+1)index_in_elem_buffer=0;
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
		int back_tail_ = tail_ == 0? capacity():tail_-1;
		return *(reinterpret_cast<value_type*>(dynamic_container_+(back_tail_*sizeof(value_type))));
	}

	const_reference back() const{
		if(empty()) throw std::logic_error{"Invalid use of back on empty BoundedBuffer"};
		int back_tail_ = tail_ == 0? capacity():tail_-1;
		return *(reinterpret_cast<value_type*>((dynamic_container_+(back_tail_*sizeof(value_type)))));
	}

	void push(value_type const & elem){
		if(full()) throw std::logic_error{"Invalid use of push on full BoundedBuffer"};
		auto pointer = reinterpret_cast<value_type*>(dynamic_container_ +(tail_*sizeof(value_type)));
		new (pointer) value_type{elem};
		tail_ = (tail_+1)%(capacity()+1);
		elements_++;
	}

	void push(value_type && elem){
		if(full()) throw std::logic_error{"Invalid use of push on full BoundedBuffer"};
		auto pointer = reinterpret_cast<value_type*>(dynamic_container_ +(tail_*sizeof(value_type)));
		new (pointer) value_type{std::move(elem)};
		tail_ = (tail_+1)%(capacity()+1);
		elements_++;
	}

	void pop(){
		if(empty()) throw std::logic_error{"Invalid use of pop on empty BoundedBuffer"};
		value_type* pointer = reinterpret_cast<value_type*>(dynamic_container_ + (head_*sizeof(value_type)));
		pointer->~T();
		head_ = (head_+1)%(capacity()+1);
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
		return init_iterator<>(true);
	}

	iterator end(){
		return init_iterator<>(false);
	}

	const_iterator begin() const{
		return init_iterator<const_iterator,const_value_type>(true);
	}

	const_iterator end() const{
		return init_iterator<const_iterator,const_value_type>(false);
	}

	const_iterator const cbegin()const{
		return begin();
	}

	const_iterator const cend()const{
		return end();
	}
};


#endif /* BOUNDEDBUFFER_H_ */
