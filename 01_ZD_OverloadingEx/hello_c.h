#ifndef HELLO_C_
#define HELLO_C_

#include <iosfwd>
#include <string>

class Hello {
	std::string memberString;
public:
	Hello(std::string str);
	void sayHello(std::ostream &o) const;
	void sayHello(std::string &str) const;
};
#endif /* HELLO_C_ */
