#include <ostream>
#include "Hello.h"

void Hello::sayHello(std::ostream &o) const{
	o << "Hello World!";
}
