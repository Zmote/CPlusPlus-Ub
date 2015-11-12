#include "w04algo.h"
#include <string>
#include <sstream>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <set>
#include <functional>
#include <locale>

bool isAlpha(const char i){
	return (!isspace(i) && !isalpha(i));
}

std::stringstream clearInputOf(std::istream &in){
	using namespace std;
	string is{};
	stringstream iss{};
	copy(istreambuf_iterator<char>(in),istreambuf_iterator<char>(),
			ostreambuf_iterator<char>(iss));
	getline(iss,is);
	is.erase(remove_if(is.begin(), is.end(), isAlpha), is.end());
	iss.clear();
	copy(begin(is),end(is),ostreambuf_iterator<char>(iss));
	return iss;
}

std::vector<std::string> generateDuplicateFreeVector(std::stringstream &ss){
	using namespace std;
	vector<string> wordList{istream_iterator<string>(ss),istream_iterator<string>()};

	transform(wordList.begin(), wordList.end(),wordList.begin(),[](string x){
		transform(x.begin(),x.end(),x.begin(),::tolower);return x;});

	set<string> mySet{begin(wordList),end(wordList)};
	wordList.clear();
	copy(begin(mySet), end(mySet), back_inserter(wordList));
	return wordList;
}

void wlist(std::ostream &out, std::istream &in){
	using namespace std;
	stringstream css = clearInputOf(in);
	vector<string> wordSet = generateDuplicateFreeVector(css);

	sort(wordSet.begin(),wordSet.end(),[&](string i, string j){
		return (tolower(i[0]) < tolower(j[0]));
	});

	ostream_iterator<string> out_it{out,"\n"};
	copy(begin(wordSet),end(wordSet),out_it);
}

int countingToLower(std::string &str){
	//is this a good design? It isn't? Why?
	using namespace std;
	int counter{0};
	transform(str.begin(),str.end(),str.begin(),[&](char i){
		char modifiedChar = tolower(i);
		if(i != modifiedChar){
			counter++;
		}
		return modifiedChar;});
return counter;
}

void printFunctionTable(std::ostream &out, const double start, const double end,
		const double steps, const std::function<double(double)> func){
	using namespace std;
	//TODO: optimize into separate methods
	vector<double> vec(steps+1);
	vec[0] = start;
	double stepSize = (end-start)/steps;
	double step = 0.0;
	generate(++vec.begin(),vec.end(),[&](){
		step += stepSize;
		return start + step;
	});
	out << "x: ";
	for_each(vec.begin(),vec.end(),[&](auto i){
		out << i << " ";
	});
	out << "\n";
	out << "f(x): ";
	for_each(vec.begin(),vec.end(),[&](auto i){
		out << func(i) << " ";
	});
	out << "\n";
}




