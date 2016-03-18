#ifndef LARGE_NUMS_H_
#define LARGE_NUMS_H_
#include <iosfwd>

void printLargeNumber(std::ostream &o, std::istream &in);
void printLargeNumber(std::ostream &o, std::istream &in, int scale);
void printLargeNumber(std::ostream &o, int in);

void printSingleLNumber(std::ostream &o,std::istream &in);
void printSingleLNumber(std::ostream &o,int in);

void sumi(std::ostream &o,std::istream &in);
void sumd(std::ostream &o,std::istream &in);
void multab(std::ostream &o,std::istream &in);
void fractab(std::ostream &o,std::istream &in);

int charc(std::istream &in);
int allac(std::istream &in);
int allcharc(std::istream &in);
int wc(std::istream &in);
int lc(std::istream &in);

#endif /* LARGE_NUMS_H_ */
