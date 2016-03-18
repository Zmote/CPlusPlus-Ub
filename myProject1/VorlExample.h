/*
 * VorlExample.h
 *
 *  Created on: 16.09.2015
 *      Author: Zmotions
 */

#ifndef VORLEXAMPLE_H_
#define VORLEXAMPLE_H_
#include <ostream>
class VorlExample {
public:
	void sayHello(std::ostream &out){
		out << "Hello World!\n";
	}
	VorlExample();
	virtual ~VorlExample();
};

#endif /* VORLEXAMPLE_H_ */
