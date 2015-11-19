#include "prime.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>

bool isPrime(const int number){
if(number == 0)return false;
std::vector<int> range(number);
iota(begin(range),end(range),1);
int count = count_if(begin(range),end(range),[&](int i){return number%i == 0;});
return count >=3? false:true;
}

void primes(std::ostream& out, const int number){
std::vector<int> range(number);
iota(begin(range),end(range),0);
range.erase(remove_if(begin(range),end(range),[](int i){return !(isPrime(i));}),range.end());
copy(begin(range),end(range),std::ostream_iterator<int>{out,"\n"});
//TODO: find a way to print new range-size(amount of primes)
out << "There are " << range.size() << " primes in the range: " << number;
}
