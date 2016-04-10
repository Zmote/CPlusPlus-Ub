#ifndef SRC_FIBONACCIITERATOR_BOOST_H_
#define SRC_FIBONACCIITERATOR_BOOST_H_

#include <boost/operators.hpp>

class FibonacciIterator : boost::input_iterator_helper<FibonacciIterator,int> {
	int result;
	int pre_old_value;
	int old_value;
	int n_value;

	FibonacciIterator& incrementFibonacci(){
		if(n_value <=0){
			++n_value;
			result = 1;
			return *this;
		}

		if(n_value > 0 && n_value < 2){
			++n_value;
			result = 1;
			return *this;
		}

		result = pre_old_value + old_value;
		pre_old_value = old_value;
		old_value = result;
		++n_value;
		return *this;
	}

public:
	explicit FibonacciIterator(int n = 0):result{0},
			pre_old_value{1}, old_value{1},n_value{0}{
				while(n_value < n){
					++(*this);
				}
			}

	bool operator==(FibonacciIterator const & fib) const{
		return n_value == fib.n_value;
	}

	int operator*()const{
		return result;
	}

	FibonacciIterator& operator++(){
		return incrementFibonacci();
	}
};



#endif /* SRC_FIBONACCIITERATOR_H_ */