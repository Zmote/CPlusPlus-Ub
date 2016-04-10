#ifndef SRC_FIBONACCIITERATOR_H_
#define SRC_FIBONACCIITERATOR_H_

#include <iterator>

struct FibonacciIterator : std::iterator<std::input_iterator_tag,int>{
	explicit FibonacciIterator(value_type n = 0):n_value{n}{}
	value_type operator*()  const{
		return calculateFibonacci(n_value);
	}
	bool operator==(FibonacciIterator const & fit) const{
		return n_value == fit.n_value;
	}

	bool operator!=(FibonacciIterator const & fit) const{
		return !(*this == fit);
	}
	FibonacciIterator& operator++(){
		++n_value;
		return *this;
	}

	FibonacciIterator operator++(int){
		auto old = *this;
		++(*this);
		return old;
	}

	static value_type calculateFibonacci(value_type n){
		if(n <=0) return 0;
		if(n > 0 && n < 3) return 1;
		int result{0};
		int pre_old_result{1};
		int old_result{1};

		for(int i=0; i < n-2;i++){
			result = pre_old_result + old_result;
			pre_old_result = old_result;
			old_result = result;
		}
		return result;
	}

private:

	value_type n_value;
};



#endif /* SRC_FIBONACCIITERATOR_H_ */