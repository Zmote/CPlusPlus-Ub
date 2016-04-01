#include "BoundedBuffer.h"
#include <iostream>

int main(){
	BoundedBuffer<int> buffer{23};

	buffer.push(1);
	buffer.push(2);

	buffer.push_many(10,23,345,34,34);
	while(buffer.size() != 0){
		std::cout << buffer.front() << "\n";
		buffer.pop();
	}
}
