#ifndef POCKETCALCULATOR_H_
#define POCKETCALCULATOR_H_
#include <iosfwd>

class Pocketcalculator{
	static std::string first;
public:
	static int calculate(std::istream& in);
	static void calculate(std::ostream& o, std::istream& in);
	static void calculate(std::ostream& o, std::istream& in, int const scale);
private:
	static bool checkInput(std::string &str, unsigned int screenDigitLimit);
	static std::string buildOutput(std::istringstream &inputStream, unsigned int screenDigitLimit);
};

#endif /* POCKETCALCULATOR_H_ */