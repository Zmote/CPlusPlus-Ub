#include <iostream>

//Separate Section of Demo
//struct Base1 {
//	Base1() {
//		std::cout << "Base1; ";
//	}
//};
//
//struct Base2 {
//	Base2() {
//		std::cout << "Base2; ";
//	}
//};
//
//struct Derived: Base1, Base2 {
//	Derived() :
//			Base2 { }, Base1 { } {
//		std::cout << "Derived; ";
//	}
//};
//
//int main(int argc, char **argv) {
//	Derived d { };
//}

//Without virtual
//struct Building {
//Building(std::string const & location) : location { location } {}
//std::string location;
//};
//struct Skyscraper : public Building {
//Skyscraper(std::string const & location, unsigned height) : Building { location }, height { height } {}
//unsigned height;
//};
//struct Hotel : public Building {
//Hotel(std::string const & location, unsigned rooms) : Building { location }, rooms { rooms } {}
//unsigned rooms;
//};
//struct SkyscraperHotel : public Skyscraper, public Hotel {
//SkyscraperHotel() : Skyscraper("somewhere", 100), Hotel("elsewhere", 200) {}
//};
//int main(int argc, char **argv) {
//SkyscraperHotel sh { };
//std::cout << "Skyscraper location: " << sh.Skyscraper::location << std::endl;
//std::cout << "Hotel location: " << sh.Hotel::location << std::endl;
//}

struct Building {
Building(std::string const & location) : location { location } {}
std::string location;
};
struct Skyscraper : public virtual Building {
Skyscraper(std::string const & location, unsigned height) : Building { location }, height { height } {}
unsigned height;
};
struct Hotel : public virtual Building {
Hotel(std::string const & location, unsigned rooms) : Building { location }, rooms { rooms } {}
unsigned rooms;
};
struct SkyscraperHotel : public Skyscraper, public Hotel {
SkyscraperHotel() : Building{"here"}, Skyscraper{"somewhere", 100}, Hotel{"elsewhere", 200} {}
};
int main(int argc, char **argv) {
SkyscraperHotel sh { };
std::cout << "Skyscraper location: " << sh.Skyscraper::location << std::endl;
std::cout << "Hotel location: " << sh.Hotel::location << std::endl;
}

