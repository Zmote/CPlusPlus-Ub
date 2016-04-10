#include "BoundedBuffer.h"
#include "NonDefaultConstructible.h"
#include <iostream>

int main(){
//	BoundedBuffer<int> buffer{23};
//
//	buffer.push(1);
//	buffer.push(2);
//
//	buffer.push_many(10,23,345,34,34);
//	while(buffer.size() != 0){
//		std::cout << buffer.front() << "\n";
//		buffer.pop();
//	}

	BoundedBuffer<X> buffer{23};
	buffer.push(X{3});
	buffer.push(X{3});
	buffer.push(X{3});
	buffer.push(X{5});
	buffer.push(X{13});
	buffer.push(X{34});
	while(buffer.size()!=0){
		std::cout << buffer.front().x << "\n";
		buffer.pop();
	}

//	BoundedBuffer<Y> buffer{23};
//	buffer.push(Y{});
//	buffer.push(Y{});
//	buffer.push(Y{});
//	buffer.push(Y{});
//	buffer.push(Y{});
//	buffer.push(Y{});
//	while(buffer.size()!=0){
//		std::cout << buffer.front().y << "\n";
//		buffer.pop();
//	}
}