#ifndef W04ALGO_H_
#define W04ALGO_H_
#include <iosfwd>
#include <string>
#include <functional>
#include <valarray>

void wlist(std::ostream &out, std::istream &in);
int countingToLower(std::string &str);
void printFunctionTable(std::ostream &out, const double start, const double end,
		const double steps, const std::function<double(double)> func);

#endif /* W04ALGO_H_ */
