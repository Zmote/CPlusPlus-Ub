#ifndef SEVENSEGMENT_H_
#define SEVENSEGMENT_H_

#include <iosfwd>

void printLargeNumber(std::ostream &o, std::istream &in);
void printLargeNumber(std::ostream &o, int in);

void printSingleLNumber(std::ostream &o,std::istream &in);
void printSingleLNumber(std::ostream &o,int in);

int charc(std::istream &in);
int allcharc(std::istream &in);
int wc(std::istream &in);
int lc(std::istream &in);


#endif /* SEVENSEGMENT_H_ */
