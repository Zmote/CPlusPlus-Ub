#ifndef NONDEFAULTCONSTRUCTIBLE_H_
#define NONDEFAULTCONSTRUCTIBLE_H_

struct X{
	//This is the extra exercise, how to create a dynamically an array of a type, that doesn't have
	//a default constructor
	//X():x{0}{}
	X(int i):x{i}{}
	int x;
};

struct Y{
	//This is the extra exercise, how to create a dynamically an array of a type, that doesn't have
	//a default constructor
	//X():x{0}{}
	Y():y{0}{}
	int y;
};

#endif /* NONDEFAULTCONSTRUCTIBLE_H_ */
