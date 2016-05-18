#ifndef SRC_BOUNDEDQUEUE_H_
#define SRC_BOUNDEDQUEUE_H_

#include <stdexcept>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <chrono>

//TODO: Tests green, but sometimes it takes a long time to continue

template<typename T,typename M = std::mutex,typename CV = std::condition_variable>
class BoundedQueue{
public:
	using value_type = T;
	using size_type = std::size_t;
	using reference = T &;
	using const_reference = T const &;
	using ulock = std::unique_lock<M>;

	BoundedQueue(size_type const q_size)
	:queue_size_{q_size},elements_{0},head_{0},
	queue_{std::make_unique<char[]>(queue_size_*sizeof(T))}{
		if(queue_size_ <= 0) throw std::invalid_argument{"BoundedQueue can't be empty"};
	}

	BoundedQueue(BoundedQueue const & other_queue)
	:BoundedQueue{other_queue.queue_size_}{
		ulock lock{other_queue.lock_};
		if(!other_queue.doempty()){
			for(unsigned int i = 0; i < other_queue.elements_;i++){
				value_type const & elem_in_queue =
						*other_queue.get_element_pointer_at(((other_queue.head_ + i)%other_queue.docapacity()));
				this->dopush(elem_in_queue);
			}
		}
	}

	BoundedQueue(BoundedQueue && other_queue){
		swap(other_queue);
	}

	~BoundedQueue(){
		ulock lock{this->lock_};
		clear();
	}

	BoundedQueue & operator=(BoundedQueue const & other_queue) noexcept {
		//TODO: Ask --> why do I need to hold lock here too,
		//the copy-ctr and swap do already lock one or both of the buffers
		if(this != &other_queue){
			BoundedQueue temporaryBuffer{other_queue};
			swap(temporaryBuffer);
		}
		return *this;
	}

	BoundedQueue & operator=(BoundedQueue && other_queue) noexcept {
		if(this != &other_queue){
			this->swap(other_queue);
		}
		return *this;
	}

	bool empty() const noexcept{
		ulock lock{this->lock_};
		return doempty();
	}
	bool full() const noexcept{
		ulock lock{this->lock_};
		return dofull();
	}
	size_type size() const noexcept{
		ulock lock{this->lock_};
		return dosize();
	}
	size_type capacity() const noexcept{
		ulock lock{this->lock_};
		return docapacity();
	}

	value_type pop(){
		ulock lock{this->lock_};
		notEmpty.wait(lock,[this]{return !doempty();});
		value_type to_return = dopop();
		notFull.notify_one();
		return to_return;
	}

	bool try_pop(reference elem){
		ulock lock{this->lock_};
		if(doempty()){
			return false;
		}
		elem = this->dopop();
		notFull.notify_one();
		return true;
	}

	bool try_pop_for(reference elem, std::chrono::duration<float> timespan){
		ulock lock{this->lock_};
		if(notEmpty.wait_for(lock,timespan,[this]{return !doempty();})){
			elem = this->dopop();
			notFull.notify_one();
			return true;
		}
		return false;
	}

	void push(const_reference elem){
		ulock lock{this->lock_};
		notFull.wait(lock,[this]{return !this->dofull();});
		dopush(elem);
		notEmpty.notify_one();
	}

	void push(value_type && elem){
		ulock lock{this->lock_};
		notFull.wait(lock,[this]{return !this->dofull();});
		dopush(std::move(elem));
		notEmpty.notify_one();
	}

	bool try_push(value_type const & elem){
		ulock lock{this->lock_};
		if(dofull())
			return false;
		this->dopush(elem);
		notEmpty.notify_one();
		return true;
	}

	bool try_push(value_type && elem){
		ulock lock{this->lock_};
		if(dofull())
			return false;
		this->dopush(std::move(elem));
		notEmpty.notify_one();
		return true;
	}

	bool try_push_for(const_reference elem, std::chrono::duration<float> timespan){
		ulock lock{this->lock_};
		if(notFull.wait_for(lock,timespan,[this]{return !dofull();})){
			this->dopush(elem);
			notEmpty.notify_one();
			return true;
		}
		return false;
	}

	bool try_push_for(value_type && elem, std::chrono::duration<float> timespan){
		ulock lock{this->lock_};
		if(notFull.wait_for(lock,timespan,[this]{return !dofull();})){
			this->dopush(std::move(elem));
			notEmpty.notify_one();
			return true;
		}
		return false;
	}

	void swap(BoundedQueue & other_queue){
		ulock otherlock{other_queue.lock_,std::defer_lock};
		ulock lock{this->lock_,std::defer_lock};
		//TODO: check if this is supposed to be done differently
		try{
			std::lock(otherlock,lock);
		}catch(std::system_error const & ex){
			throw std::logic_error{"Lock aqcquire failed"};
		}
		std::swap(queue_,other_queue.queue_);
		std::swap(elements_,other_queue.elements_);
		std::swap(queue_size_,other_queue.queue_size_);
		std::swap(head_,other_queue.head_);
	}

private:
	size_type queue_size_{};
	size_type elements_{};
	size_type head_{};
	std::unique_ptr<char[]> queue_;
	mutable M lock_{};
    CV notEmpty{};
    CV notFull{};

	void dopush(const_reference elem){
		if(dofull()) throw std::logic_error{"Can't push to full Queue"};
		new (get_element_pointer_at(tail())) value_type{elem};
		elements_++;
	}

	void dopush(value_type && elem){
		if(dofull()) throw std::logic_error{"Can't push to full Queue"};
		new (get_element_pointer_at(tail())) value_type{std::move(elem)};
		elements_++;
	}

	value_type dopop(){
		if(doempty()) throw std::logic_error{"Can't pop from empty Queue"};
		value_type * value_to_pop = get_element_pointer_at(head_);
		value_type return_value{std::move(*value_to_pop)};
		value_to_pop->~T();
		head_ = (head_ + 1) % (docapacity());
		elements_--;
		return return_value;
	}

	bool doempty() const noexcept{
		return elements_ == 0;
	}

	bool dofull() const noexcept{
		return elements_ == queue_size_;
	}

	size_type dosize() const noexcept{
		return elements_;
	}

	size_type docapacity() const noexcept{
		return queue_size_;
	}

	void doswap(BoundedQueue & other_queue){
		std::swap(queue_,other_queue.queue_);
		std::swap(elements_,other_queue.elements_);
		std::swap(queue_size_,other_queue.queue_size_);
		std::swap(head_,other_queue.head_);
	}

	void clear(){
		while(!doempty()){
			get_element_pointer_at(head_)->~T();
			head_ = (head_ + 1) % (docapacity());
			elements_--;
		}
	}

	value_type * get_element_pointer_at(size_type index) const noexcept{
		return reinterpret_cast<value_type*>(queue_.get()) + index;
	}

	size_type tail() const{
		return (head_ + elements_) % docapacity();
	}
};


#endif /* SRC_BOUNDEDQUEUE_H_ */
