#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

//const size_t SZ = 6*7;
//double x[SZ];
//
//template <size_t n>
//struct fact{
//	static size_t const value = (n * fact<n-1>::value);
//};
//
//template <>
//struct fact<0>{
//	static size_t const value = 1;
//};
//
//int a[fact<5>::value];

constexpr unsigned long long fact(unsigned short n){
	return n>1?n*fact(n-1):1;
}
int a[fact(5)];

constexpr double factd(unsigned short n){
	return n>1?n*factd(n-1):1;
}

constexpr auto fact5=factd(5);
static_assert(120==fact5,"see if doubles comare equal");

template <typename T>
constexpr T abs(T x){
	return x<0?-x:x;
}

static_assert(5 == abs(-5),"abs is correct for negative int");
static_assert(5 == abs(5),"abs is correct for positive int");
static_assert(5.0 == abs(-5.0),"abs is correct for negative double");
static_assert(5.0l == abs(-5.0l),"abs is correct for negative long double");

void testFactorialCompiletime(){
//	size_t x = fact<4>::value;
	ASSERT_EQUAL(sizeof(a),sizeof(int)*2*3*4*5);
//	ASSERT_EQUAL(x,24);
}

void testFactDouble(){
	int i = 3+fact(2);
	ASSERT_EQUAL(120.0,factd(i));
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	s.push_back(CUTE(testFactorialCompiletime));
	s.push_back(CUTE(testFactDouble));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



