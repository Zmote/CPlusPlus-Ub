#ifndef CALC_H_
#define CALC_H_
#include <iosfwd>

int calc(int a, int b, char op);
int calc(std::istream& in);
void print(std::ostream& out, int a, int b, char op, int number);

#endif /* CALC_H_ */
