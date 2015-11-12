#ifndef DATE_H_
#define DATE_H_

#include <iosfwd>

/*
 struct Date{
 */
class Date {
public:
	//Starts with sunday, because of gauss algorithm
	enum class Day: int{Sonntag, Montag,Dienstag,Mittwoch,Donnerstag,Freitag,Samstag};
public:
	enum Month{Januar=1,Februar,Maerz,April,Mai,Juni,Juli,August,September,Oktober,November,Dezember};
	int year,month ,day;
public:
	void print(std::ostream& out) const;
	std::string day_of_week();
	static bool isValidYear(int year);
	static bool isLeapYear(int year);
	static bool isValidDate(int year, Month month, int day);
	Date(int year, Month month, int day);
	//Date(int day, Month month, int year) funktioniert nicht,
	//da es nicht auf parameter name basierend die Overloads überpüft,
	//sondern anhand des Typs.
	Date(Month month, int day,int year);
	static int endOfMonth(int year, int month);
	void nextDay();
	bool operator <(Date const& rhs) const;

	/*
	 private:
	 int year, month, day;
	 */

};

inline bool operator>(Date const& lhs, Date const& rhs) {
	return rhs < lhs;
}
inline bool operator>=(Date const& lhs, Date const& rhs) {
	return !(lhs < rhs);
}
inline bool operator<=(Date const& lhs, Date const& rhs) {
	return !(rhs < lhs);
}

inline bool operator==(Date const& lhs, Date const& rhs) {
	return !(lhs < rhs) && !(rhs < lhs);
}
inline bool operator!=(Date const& lhs, Date const& rhs) {
	return !(lhs == rhs);
}

#endif /* DATE_H_ */
