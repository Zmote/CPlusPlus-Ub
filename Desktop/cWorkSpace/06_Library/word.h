#ifndef WORD_H_
#define WORD_H_

#include <iosfwd>
#include <string>
#include <ostream>

class Word{
std::string word;
public:
	Word() = default;
	explicit Word(std::string c);
	void print(std::ostream& o);
	void read(std::istream& i);
	std::string toLower() const;

	bool operator<(Word const  &rhs) const
	{return toLower() < rhs.toLower(); }
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
inline bool operator==(Word const &lhs, Word const &rhs){
	return !(rhs<lhs) && !(rhs>lhs);
}
inline bool operator!=(Word const &lhs, Word const &rhs){
	return !(rhs==lhs);
}
inline bool operator>=(Word const &lhs, Word const &rhs){
	return !(lhs<rhs);
}
inline bool operator<=(Word const &lhs, Word const &rhs){
	return !(rhs<lhs);
}


#endif /* WORD_H_ */
