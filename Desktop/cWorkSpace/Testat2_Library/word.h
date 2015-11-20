#ifndef WORD_H_
#define WORD_H_

#include <iosfwd>
#include <string>
#include <ostream>
#include <algorithm>
#include <cctype>

class Word{
std::string word;
public:
	Word() = default;
	explicit Word(std::string c);
	void print(std::ostream& o);
	void read(std::istream& in);
	bool operator<(Word const  &rhs) const{
		return std::lexicographical_compare(begin(word),end(word),
				begin(rhs.word),end(rhs.word),[](char l, char r){
			return std::tolower(l) < std::tolower(r);
		});
	}
};

inline std::ostream& operator<<(std::ostream& out,Word& word){
	word.print(out);
	return out;
}
inline std::istream& operator>>(std::istream& in,Word& word){
	word.read(in);
	return in;
}
inline bool operator>(Word const &lhs, Word const  &rhs){
	return rhs < lhs;
}
inline bool operator>=(Word const &lhs, Word const &rhs){
	return !(lhs<rhs);
}
inline bool operator<=(Word const &lhs, Word const &rhs){
	return !(rhs<lhs);
}
inline bool operator==(Word const &lhs, Word const &rhs){
	return !(lhs<rhs) && !(rhs<lhs);
}
inline bool operator!=(Word const &lhs, Word const &rhs){
	return !(lhs==rhs);
}


#endif /* WORD_H_ */
