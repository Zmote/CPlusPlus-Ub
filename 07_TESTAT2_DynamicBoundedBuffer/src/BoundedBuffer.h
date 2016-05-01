#ifndef BOUNDEDBUFFER_H_
#define BOUNDEDBUFFER_H_

#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <boost/operators.hpp>

template<typename T>
class BoundedBuffer {
	unsigned int head_ { 0 };
	unsigned int elements_ { 0 };
	char * dynamic_container_ = nullptr;
	unsigned int dynamic_container_size_ { 0 };

public:
	using size_type = std::size_t;
	using value_type = T;
	using const_reference = T const &;
	using reference = T &;

private:
	value_type * get_element_pointer_at(size_type index) const noexcept{
		return (reinterpret_cast<value_type*>(dynamic_container_ + (index * sizeof(value_type))));
	}

	void fill_buffer_from(const BoundedBuffer& elem) {
		auto elembuffer = reinterpret_cast<value_type*>(elem.dynamic_container_);
		if (elem.size() > 0) {
			BoundedBuffer temporary{elem.capacity()};
			size_t index_in_elem_buffer = &elem.front() - elembuffer;
			for (unsigned int i = 0; i < elem.size(); i++) {
				temporary.push(elembuffer[index_in_elem_buffer++]);
				if (index_in_elem_buffer >= elem.capacity())
					index_in_elem_buffer = 0;
			}
			*this = std::move(temporary);
		}
	}
	void check_if_front_accessible() const {
		if (empty())
			throw std::logic_error { "Invalid use of front on empty BoundedBuffer" };
	}

	void check_if_back_accessible() const {
		if (empty())
			throw std::logic_error { "Invalid use of back on empty BoundedBuffer" };
	}

	void check_if_pushable() {
		if (full())
			throw std::logic_error { "Invalid use of push on full BoundedBuffer" };
	}

	void initialize_container(size_type container_capacity) noexcept {
		dynamic_container_ = new char[(container_capacity) * sizeof(T)];
		dynamic_container_size_ = container_capacity;
	}

	int calculate_back_tail_index() const {
		if(!capacity()) throw std::invalid_argument{"Modulo through zero not possible"};
		return tail() == 0 ? capacity() - 1 : tail() - 1;
	}

	template<typename TYPE = value_type>
	struct iter: boost::random_access_iterator_helper<iter<TYPE>, TYPE> {
		using difference_type = typename iter::difference_type;

		explicit iter(BoundedBuffer const & input_buff, size_type input_index) noexcept :
				buffer { input_buff }, index { input_index }{}

		value_type & operator[](int iter_index) const {
			return buffer[buffer.head_ + iter_index];
		}

		value_type & operator=(const iter & rhs) {
			buffer = rhs.buffer;
			index = rhs.index;
			return *this;
		}

		value_type & operator*() const {
			check_if_iterator_at_end();
			return buffer[index];
		}

		iter & operator++() {
			check_if_iterator_at_end();
			increment_index();
			return *this;
		}

		iter & operator+(size_type distance) {
			for (unsigned int i = 0; i < distance; i++) {
				++(*this);
			}
			return *this;
		}

		iter & operator--() {
			check_if_iterator_at_start();
			decrement_iterator();
			return *this;
		}

		iter & operator-(size_type distance) {
			for (unsigned int i = 0; i < distance; i++) {
				--(*this);
			}
			return *this;
		}

		difference_type operator-(iter const & rhs) {
			check_if_buffers_same(rhs);
			difference_type diff { 0 };
			iter internal = rhs;
			while (index != internal.index) {
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
		bool operator==(const iter & rhs) const {
			check_if_buffers_same(rhs);
			return index == rhs.index;
		}
		bool operator<(const iter & rhs) const {
			check_if_buffers_same(rhs);
			return index < rhs.index;
		}
		value_type * operator->() const {
			return reinterpret_cast<value_type *>(buffer.dynamic_container_);
		}

	private:
		BoundedBuffer const & buffer;
		size_type index;

		void check_if_buffers_same(iter const & rhs) const {
			if (buffer.dynamic_container_ != rhs.buffer.dynamic_container_)
				throw std::logic_error { "Relative comparison on different buffers not possible" };
		}
		void check_if_iterator_at_end() const {
			if (index == buffer.elements_)
				throw std::logic_error { "Can't access element at end" };
		}
		void increment_index() {
			index = (index + 1) % (buffer.capacity() + 1);
		}
		void decrement_iterator() {
			index = index == 0 ? buffer.capacity() : index - 1;
		}
		void check_if_iterator_at_start() const {
			if (index == 0)
				throw std::logic_error { "Can't decreement below begin" };
		}
	};

public:
	using iterator = iter<>;
	using const_iterator = iter<const value_type>;

	void clear() noexcept {
		while (!empty())
			pop();
		head_ = 0;
	}

	BoundedBuffer():head_ { 0 }, elements_ { 0 }, dynamic_container_ { nullptr }, dynamic_container_size_ { 0 } {}

	~BoundedBuffer(){
		while(!empty())
			dopop();
		delete[] dynamic_container_;
	}

	BoundedBuffer(size_type const buffer_size):head_ { 0 }, elements_ { 0 } {
		if (buffer_size <= 0)
			throw std::invalid_argument { "Capacity of BoundedBuffer can't be zero" };
		initialize_container(buffer_size);
	}

	BoundedBuffer(BoundedBuffer const & elem) {
		initialize_container(elem.capacity());
		fill_buffer_from(elem);
	}

	BoundedBuffer(BoundedBuffer && elem) noexcept {
		swap(elem);
	}

	BoundedBuffer & operator=(BoundedBuffer const & elem) noexcept{
		if (this != &elem) {
			BoundedBuffer temporaryBuffer{elem};
			swap(temporaryBuffer);
		}
		return *this;
	}

	BoundedBuffer & operator=(BoundedBuffer && elem) noexcept{
		if (this != &elem) {
			swap(elem);
		}
		return *this;
	}

	value_type & operator[](int index) const {
		int limit = capacity();
		if (index >= limit || index <= -limit) throw std::out_of_range { "Out of bounds access" };
		int access_index { 0 };
		if (index >= 0 && index < limit) {access_index = (head_ + index) % capacity();}
		if (index < 0 && index > -limit) {access_index = capacity() + index;}
		return get_element_pointer_at(0)[access_index];
	}

	bool empty() const noexcept {
		return elements_ == 0;
	}

	size_type size() const noexcept {
		return elements_;
	}

	size_type capacity() const noexcept {
		return dynamic_container_size_;
	}

	size_type tail() const{
		return (head_ + elements_) % capacity();
	}

	bool full() const noexcept{
		return elements_ == capacity();
	}

	reference front() {
		check_if_front_accessible();
		return *get_element_pointer_at(head_);
	}

	const_reference front() const {
		check_if_front_accessible();
		return *get_element_pointer_at(head_);
	}

	reference back() {
		check_if_back_accessible();
		return *get_element_pointer_at(calculate_back_tail_index());
	}

	const_reference back() const {
		check_if_back_accessible();
		return *get_element_pointer_at(calculate_back_tail_index());
	}

	void push(value_type const & elem) {
		check_if_pushable();
		new (get_element_pointer_at(tail())) value_type { elem };
		elements_++;
	}

	void push(value_type && elem) {
		check_if_pushable();
		new (get_element_pointer_at(tail())) value_type { std::move(elem) };
		elements_++;
	}
private:
	void dopop() noexcept(true){
		get_element_pointer_at(head_)->~T();
		head_ = (head_ + 1) % (capacity());
		elements_--;
	}
public:
	void pop() noexcept(false) {
		if (empty()) throw std::logic_error { "Invalid use of pop on empty BoundedBuffer" };
		dopop();
	}

	void swap(BoundedBuffer & elem) noexcept{
		std::swap(dynamic_container_, elem.dynamic_container_);
		std::swap(head_, elem.head_);
		std::swap(elements_, elem.elements_);
		std::swap(dynamic_container_size_, elem.dynamic_container_size_);
	}

	void push_many() {

	}

	template<typename FIRST, typename ...REST>
	void push_many(FIRST && first, REST&&...rest) {
		push(std::forward<FIRST>(first));
		push_many(std::forward<decltype(rest)>(rest)...);
	}

	template<typename ...TYPE>
	static BoundedBuffer<value_type> make_buffer(const int size, TYPE&&...param) {
		if(sizeof...(TYPE) > size)throw std::invalid_argument {"Invalid argument"};
		BoundedBuffer<value_type> buffer {size};
		buffer.push_many(std::forward<TYPE>(param)...);
		return buffer;
	}

	iterator begin() noexcept {
		return iterator {*this,0};
	}

	iterator end() noexcept {
		return iterator {*this,elements_};
	}

	const_iterator begin() const noexcept {
		return const_iterator {*this,0};
	}

	const_iterator end() const noexcept {
		return const_iterator {*this,elements_};
	}

	const_iterator const cbegin()const noexcept{
		return begin();
	}

	const_iterator const cend()const noexcept{
		return end();
	}
};

#endif /* BOUNDEDBUFFER_H_ */
