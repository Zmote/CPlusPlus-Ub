#ifndef POCKETCALCULATOR_H_
#define POCKETCALCULATOR_H_
#include <iosfwd>

int calculate(std::istream& in);
void calculate(std::ostream& o, std::istream& in);
void calculate(std::ostream& o, std::istream& in, int const scale);

#endif /* POCKETCALCULATOR_H_ */
