#ifndef CALC_H_
#define CALC_H_
#include <iosfwd>

class Calculator{

public:
	static int calc(int const a, int const b, char const op);
	static int calc(std::istream &in);
};

#endif /* CALC_H_ */
