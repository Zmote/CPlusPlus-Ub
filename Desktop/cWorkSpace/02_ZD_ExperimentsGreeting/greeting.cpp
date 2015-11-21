#include <iostream>
#include <string>
void askForName(std::ostream &out){
  out << "What is your name? ";
}
std::string inputName(std::istream &in){
  std::string name{};
  in >> name;
  return name;
}
void sayGreeting(std::ostream &out,std::string name, std::string name2){
	out << "Hello " << name << ", how are you?\n" << name2;
}
int main() {
  askForName(std::cout);
  sayGreeting(std::cout, inputName(std::cin), inputName(std::cin));
}

/*
 * No, the sequence of names isn't the same, the last entered string value
 * is shown first.
 * No, when the first input is wrong(and thus fails), the stream is put into .fail() state.
 * It would be better to use a seperate istringstream variable to store
 * the value and to continue workingw with that file. --> sample of the
 * principle should be availbe in script of lecture
 * */
