#ifndef BOUNDEDBUFFER_H_
#define BOUNDEDBUFFER_H_

#include <stdexcept>
#include <iterator>
#include <boost/operators.hpp>

template<typename T>
class BoundedBuffer {
public:
	using size_type = std::size_t;
	using value_type = T;
	using const_reference = T const &;
	using reference = T &;

private:
	unsigned int head_ { 0 };
	unsigned int elements_ { 0 };
	char * dynamic_container_ = nullptr;
	unsigned int dynamic_container_size_ { 0 };

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
			index = (index + 1) % (buffer.capacity() + 1);
			return *this;
		}

		iter & operator+=(difference_type distance) {
			check_if_iterator_at_end();
			index = (index + distance)%(buffer.capacity()+1);
			return *this;
		}

		iter & operator--() {
			if (index == 0) throw std::logic_error { "Can't decreement below begin" };
			index = index == 0 ? buffer.capacity() : index - 1;
			return *this;
		}

		iter & operator-=(size_type distance) {
			if(((int)index-(int)distance) <= 0) throw std::logic_error{"Can't iteratore below start"};
			index = (index - distance)%(buffer.capacity()+1);
			return *this;
		}

		difference_type operator-(iter const & rhs) const{
			check_if_buffers_same(rhs);
			return difference_type(index) - difference_type(rhs.index);
		}

		bool operator==(const iter & rhs) const {
			check_if_buffers_same(rhs);
			return index == rhs.index;
		}
		bool operator<(const iter & rhs) const {
			check_if_buffers_same(rhs);
			return index < rhs.index;
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
	};

	value_type * get_element_pointer_at(size_type index) const noexcept{
		return reinterpret_cast<value_type*>(dynamic_container_ + (index * sizeof(value_type)));
	}

	void initialize_container(size_type container_capacity) {
		dynamic_container_ = new char[(container_capacity) * sizeof(T)];
		dynamic_container_size_ = container_capacity;
	}

	size_type tail() const{
		return (head_ + size()) % capacity();
	}

	int calculate_back_tail_index() const {
		return tail() == 0 ? capacity() - 1 : tail() - 1;
	}

	void dopop() noexcept{
		get_element_pointer_at(head_)->~T();
		head_ = (head_ + 1) % (capacity());
		elements_--;
	}

	value_type & operator[](int index) const {
		int limit = capacity();
		if (index >= limit || index <= -limit) throw std::out_of_range { "Out of bounds access" };
		int access_index { 0 };
		if (index >= 0 && index < limit) {access_index = (head_ + index) % capacity();}
		if (index < 0 && index > -limit) {access_index = capacity() + index;}
		return get_element_pointer_at(0)[access_index];
	}

	void check_not_empty() const{
		if (empty()) throw std::logic_error { "Invalid use of operation on empty BoundedBuffer" };
	}

	void check_not_full() const{
		if (full()) throw std::logic_error { "Invalid use of operation on full BoundedBuffer" };
	}

public:
	using iterator = iter<>;
	using const_iterator = iter<const value_type>;

	void clear() noexcept {
		while (!empty())
			dopop();
	}

	BoundedBuffer():head_ { 0 }, elements_ { 0 }, dynamic_container_ { nullptr }, dynamic_container_size_ { 0 } {}

	~BoundedBuffer(){
		clear();
		delete[] dynamic_container_;
	}

	BoundedBuffer(size_type const buffer_size):head_ { 0 }, elements_ { 0 } {
		if (buffer_size == 0)
			throw std::invalid_argument { "Capacity of BoundedBuffer can't be zero" };
		initialize_container(buffer_size);
	}

	BoundedBuffer(BoundedBuffer const & elem) {
		initialize_container(elem.capacity());
		for (auto const &x:elem) push(x);
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
		swap(elem);
		return *this;
	}

	size_type size() const noexcept {
		return elements_;
	}

	bool empty() const noexcept {
		return size() == 0;
	}

	size_type capacity() const noexcept {
		return dynamic_container_size_;
	}

	bool full() const noexcept{
		return size() == capacity();
	}

	reference front() {
		check_not_empty();
		return *get_element_pointer_at(head_);
	}

	const_reference front() const {
		check_not_empty();
		return *get_element_pointer_at(head_);
	}

	reference back() {
		check_not_empty();
		return *get_element_pointer_at(calculate_back_tail_index());
	}

	const_reference back() const {
		check_not_empty();
		return *get_element_pointer_at(calculate_back_tail_index());
	}

	void push(value_type const & elem) {
		check_not_full();
		new (get_element_pointer_at(tail())) value_type { elem };
		elements_++;
	}

	void push(value_type && elem) {
		check_not_full();
		new (get_element_pointer_at(tail())) value_type { std::move(elem) };
		elements_++;
	}

	void pop(){
		check_not_empty();
		dopop();
	}

	void swap(BoundedBuffer & elem) noexcept{
		std::swap(dynamic_container_, elem.dynamic_container_);
		std::swap(head_, elem.head_);
		std::swap(elements_, elem.elements_);
		std::swap(dynamic_container_size_, elem.dynamic_container_size_);
	}

	void push_many() {}

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
		return iterator {*this,size()};
	}

	const_iterator begin() const noexcept {
		return const_iterator {*this,0};
	}

	const_iterator end() const noexcept {
		return const_iterator {*this,size()};
	}

	const_iterator const cbegin()const noexcept{
		return begin();
	}

	const_iterator const cend()const noexcept{
		return end();
	}
};

#endif /* BOUNDEDBUFFER_H_ */
