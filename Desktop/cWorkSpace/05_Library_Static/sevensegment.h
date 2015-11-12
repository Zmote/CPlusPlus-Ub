#ifndef SEVENSEGMENT_H_
#define SEVENSEGMENT_H_

#include <iosfwd>
#include <vector>

class Sevensegment{
	static const std::vector<std::vector<std::string>> numbers;
public:
	static void printLargeNumber(std::ostream &o, std::istream &in);
	static void printLargeNumber(std::ostream &o, std::istream &in, int const scale);
	static void printSingleLNumber(std::ostream &o, std::istream &i);
private:
	static int charMapper(char const inputChar);
	static void drawLine(int i, std::string givenNumber, int scale, std::ostream & o);
};

#endif /* SEVENSEGMENT_H_ */
