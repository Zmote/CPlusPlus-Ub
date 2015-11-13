#ifndef ANSI_H_
#define ANSI_H_

#include <iosfwd>
#include <string>

namespace Ansi{
	enum colors{bblack=30,bred,bgreen,byellow,bblue,bmagenta,bcyan,bwhite,
	fblack=40,fred,fgreen,fyellow,fblue,fmagenta,fcyan,fwhite};
	std::string const ESCAPE{"\33["};
	std::string Clear();
	std::string ForeColor(unsigned color);
	std::string Blink();
	std::string BackColor(unsigned color);
	std::string Bold();
    std::string AttributeOff();
	std::string Pos(unsigned l, unsigned c);
	std::string Home();
	std::string Up(unsigned n);
	std::string Down(unsigned n);
	std::string Right(unsigned n);
	std::string Left(unsigned n);
}

#endif /* ANSI_H_ */