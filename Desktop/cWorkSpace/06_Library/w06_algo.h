#ifndef W06_ALGO_H_
#define W06_ALGO_H_

#include <iosfwd>

class  Switch{
private:
	enum class State : unsigned short;
	State currentState;
public:
	Switch();
	void pressButton();
};



#endif /* W06_ALGO_H_ */
