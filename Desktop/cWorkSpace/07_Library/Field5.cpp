#include <ostream>
#include "Field5.h"

std::ostream& operator <<(std::ostream& out, const Field5& r) {
	out << "Field5{" << r.value() << '}';
	return out;
}
