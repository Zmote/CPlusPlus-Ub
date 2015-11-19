#include "prime.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>
#include <iostream>

bool isPrime(const int number){
std::vector<int> range{number};
int n{1};
generate(begin(range),end(range),[&n](){
	return n++;
});
for_each(begin(range),end(range),[](int i){
	std::cout << i << "\n";
});
int divisions{0};
for_each(begin(range),end(range),[&](int i){
	if(number%i == 0){
		divisions++;
	}
});
return divisions >=2? false:true;
}
