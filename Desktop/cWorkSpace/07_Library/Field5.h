#ifndef Field5_H_
#define Field5_H_
#include <iosfwd>
#include <cmath>
#include <iostream>
#include <boost/operators.hpp>
//Relational ops could make sense, if were interested
//in the field values themselves, which is bigger than the other?
// but if we want to know if Field5{102} is bigger than Field5{55}
//it doesn't make much sense, no.
class Field5 {
	unsigned val;
public:
	explicit constexpr Field5(unsigned x = 0u) :
			val { x % 5 } {
	}
	constexpr unsigned value() const {
		return val;
	}
	constexpr operator unsigned() const {
		return val;
	}
	constexpr bool operator==(Field5 const &r) const {
		return val == r.val;
	}
	constexpr bool operator!=(Field5 const &r) const {
		return !(*this == r);
	}
	constexpr Field5 operator+=(Field5 const &r) {
		val = (val + r.value()) % 5;
		return *this;
	}
	constexpr Field5 operator*=(Field5 const&r) {
		val = (val * r.value()) % 5;
		return *this;
	}
	constexpr Field5 operator+(Field5 const &r) const {
		return Field5 { val + r.val };
	}
	constexpr Field5 operator-(Field5 const &r) const {
		return Field5 {(5 +( val - r.val)) };
		}
	constexpr Field5 operator-() const {
			return Field5 {5%val};
	}
	constexpr Field5 operator*(Field5 const &r) const {
		return Field5 { val * r.val };
	}
	constexpr Field5 operator/(Field5 const &r) const {
		unsigned int res{};
		for(unsigned int i = 0; i < 5; i++){
			res = (r.val * i)%5;
			if(res == val){
				return Field5 {i};
			}
		}
	}
};

namespace F5 {
constexpr Field5 operator"" _F5(unsigned long long v) {
	return Field5 { static_cast<unsigned>(v % 5) };
}
}
std::ostream& operator <<(std::ostream& out, const Field5& r);

#endif /* Field5_H_ */