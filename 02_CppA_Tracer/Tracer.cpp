#include <iostream>
#include <string>
#include <vector>
#include <chrono>

struct Tracer {
	explicit Tracer(std::string name = "") :  name { name } {
		//std::cout << "Tracer created: " << name << std::endl;
	}
	~Tracer() {
		//std::cout << "Tracer destroyed: " << name << std::endl;
	}

	Tracer(Tracer const& other) : name { other.name + " copy" } {
		//std::cout << "Tracer copied: " << name << std::endl;
	}

//	ohne std::move würde der Copy-Construcotr oder Assignment aufgerufen

////////////////////////////////////////////////////////////////////////////
// Behaviour change: sink = std::move(source) --> source zeigt auf sink	  //
// sink zeigt auf source(erwartet), aber nicht das source auf sink zeigt, //
// interessant															  //
////////////////////////////////////////////////////////////////////////////
	Tracer(Tracer && other) : name {std::move(other.name + " move")} {
		//std::cout << "Tracer moved: " << name << std::endl;
	}

///////////////////////////////////////////////////////////////////////////////////////////////
//	Da der copy-assignment operator auch erzeugt wird, wenn nicht explizit angegeben wird	 //
//	compiled der unterige Code. Der Operator wird innerhalb definiert, weil der				 //
//	assignment operator unary ist, und man darum Zugriff direkt auf das this Objekt braucht  //
//////////////////////////////////////////////////////////////////////////////////////////////

	Tracer& operator=(Tracer const & t){
		//std::cout << "copy-assigned: " << t.name << " to " << name << std::endl;
		name = t.name;
		return *this;
	}

//	Move-assignmnet operator
	Tracer& operator=(Tracer && t){
		//std::cout << "move-assigned: " << t.name << " to " << name << std::endl;
		name = std::move(t.name);
		return *this;
	}

	void show() const {
		std::cout << "Tracer: " << name << std::endl;
	}
	std::string name;
};

void foo(Tracer t) {
	Tracer trace("foo");
	t.show();
}

Tracer bar(Tracer const &t) {
	Tracer trace("bar");
	t.show();
	return trace;
}

int main(){
	std::vector<Tracer> v{};
	for(int i = 0;i < 100000;i++){
		v.push_back(Tracer("T"+i));
	}
	//vector size: ~10000
	//per move ist um einiges schneller!
	//move: 0s, copy: 0.2s
	 auto start = std::chrono::system_clock::now();
//	  std::vector<Tracer> w{v};
//	  std::vector<Tracer> z{w};
//	  std::vector<Tracer> x{z};
	  std::vector<Tracer> w{std::move(v)};
	  std::vector<Tracer> z{std::move(w)};
	  std::vector<Tracer> x{std::move(z)};
	  std::chrono::duration<double> delta = std::chrono::system_clock::now() - start;
	  std::cout << "creating the container took: " << delta.count() << "s time\n";
}

//int main() {
//  Tracer m{};
//  std::cout << "\t\t--- std::move(m) ----" << std::endl;
//  std::move(m); //nichts passiert
//  std::cout << "\t\t--- end of main ----" << std::endl;
//}

//int main() {
//  std::cout << "\t\t--- creating sink and source ----" << std::endl;
//  Tracer sink {"sink"}, source {"source"};
//  Tracer mink{"mink"};
//
//  std::cout << "\t\t--- assigning source to sink ----" << std::endl;
//  sink = std::move(source);
//
//  std::cout << "\t\t--- showing sink ----" << std::endl;
//  sink.show();
//
//  std::cout << "\t\t--- showing source ----" << std::endl;
//  source.show();
//
//  std::cout << "\t\t--- end of main ----" << std::endl;
//}

//int main() {
//  std::cout << "\t\t--- creating sink and source ----" << std::endl;
//  Tracer sink {"sink"}, source {"source"};
//
//  std::cout << "\t\t--- assigning source to sink ----" << std::endl;
//  sink = source;
//
//  std::cout << "\t\t--- showing sink ----" << std::endl;
//  sink.show();
//
//  std::cout << "\t\t--- showing source ----" << std::endl;
//  source.show();
//
//  std::cout << "\t\t--- end of main ----" << std::endl;
//}

//int main() {
////	Default: Ausgangslage
////	Tracer m { "main" };
////	{
////		Tracer inner { "inner" };
////		foo(inner);
////		auto trace = bar(inner);
////		trace.show();
////		inner.show();
////	}
////	foo(Tracer { "temp" });
////	m.show();
//	 std::vector<Tracer> v{};
//	 v.push_back(Tracer{"T1"});
//	 std::cout << "All this happened before this point ---\n";
//	 v.push_back(Tracer{"T2"});
//	 std::cout << "All this happened before this point ---\n";
//	 v.push_back(Tracer{"T3"});
//	 std::cout << "All this happened before this point ---\n";
//	 v.push_back(Tracer{"T4"});
//	 std::cout << "All this happened before this point ---\n";
//	 std::vector<Tracer> v_copy{v};
//	 std::cout << "All this happened before this point ---\n";
//
//	 //use of deleted function Trace::Tracer.. error bei Move-only Trace Klasse
//	 //std::vector<Tracer> w{v};
//
//}
