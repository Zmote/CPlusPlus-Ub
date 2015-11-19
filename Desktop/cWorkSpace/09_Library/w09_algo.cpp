#include "w09_algo.h"
#include "word.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <string>
#include <set>
#include <map>

std::vector<Word> buildVector(std::istream& in){
using it = std::istream_iterator<std::string>;
Word myword{};
std::stringstream ss{};
in >> myword;
ss << myword;
std::vector<Word> vec{it(ss),it()};
return vec;
}

std::vector<Word> getStopWordsAll(){
std::vector<std::string> stops{"i", "me", "my", "myself", "we", "our", "ours", "ourselves", "you", "your", "yours",
	"yourself", "yourselves", "he", "him", "his", "himself", "she", "her", "hers", "herself", "it", "its", "itself",
	"they", "them", "their", "theirs", "themselves", "what", "which", "who", "whom", "this", "that", "these", "those", "am",
	"is", "are", "was", "were", "be", "been", "being", "have", "has", "had", "having", "do", "does", "did", "doing", "a", "an", "the",
	"and", "but", "if", "or", "because", "as", "until", "while", "of", "at", "by", "for", "with", "about", "against", "between", "into",
	"through", "during", "before", "after", "above", "below", "to", "from", "up", "down", "in", "out", "on", "off", "over", "under", "again",
	"further", "then", "once", "here", "there", "when", "where", "why", "how", "all", "any", "both", "each", "few", "more", "most", "other",
	"some", "such", "no", "nor", "not", "only", "own", "same", "so", "than", "too", "very", "s", "t", "can", "will", "just", "don", "should",
	"now"};
std::vector<std::string> germanStops{"aber", "alle", "allem", "allen", "aller", "alles", "als", "also", "am", "an", "ander", "andere", "anderem",
	"anderen", "anderer", "anderes", "anderm", "andern", "anderr", "anders", "auch", "auf", "aus", "bei", "bin", "bis", "bist", "da", "damit",
	"dann", "der", "den", "des", "dem", "die", "das", "daß", "derselbe", "derselben", "denselben", "desselben", "demselben", "dieselbe",
	"dieselben", "dasselbe", "dazu", "dein", "deine", "deinem", "deinen", "deiner", "deines", "denn", "derer", "dessen", "dich", "dir", "du",
	"dies", "diese", "diesem", "diesen", "dieser", "dieses", "doch", "dort", "durch", "ein", "eine", "einem", "einen", "einer", "eines", "einig",
	"einige", "einigem", "einigen", "einiger", "einiges", "einmal", "er", "ihn", "ihm", "es", "etwas", "euer", "eure", "eurem", "euren", "eurer",
	"eures", "für", "gegen", "gewesen", "hab", "habe", "haben", "hat", "hatte", "hatten", "hier", "hin", "hinter", "ich", "mich", "mir", "ihr",
	"ihre", "ihrem", "ihren", "ihrer", "ihres", "euch", "im", "in", "indem", "ins", "ist", "jede", "jedem", "jeden", "jeder", "jedes", "jene",
	"jenem", "jenen", "jener", "jenes", "jetzt", "kann", "kein", "keine", "keinem", "keinen", "keiner", "keines", "können", "könnte", "machen",
	"man", "manche", "manchem", "manchen", "mancher", "manches", "mein", "meine", "meinem", "meinen", "meiner", "meines", "mit", "muss",
	"musste", "nach", "nicht", "nichts", "noch", "nun", "nur", "ob", "oder", "ohne", "sehr", "sein", "seine", "seinem", "seinen", "seiner",
	"seines", "selbst", "sich", "sie", "ihnen", "sind", "so", "solche", "solchem", "solchen", "solcher", "solches", "soll", "sollte", "sondern",
	"sonst", "über", "um", "und", "uns", "unse", "unsem", "unsen", "unser", "unses", "unter", "viel", "vom", "von", "vor", "während", "war",
	"waren", "warst", "was", "weg", "weil", "weiter", "welche", "welchem", "welchen", "welcher", "welches", "wenn", "werde", "werden", "wie",
	"wieder", "will", "wir", "wird", "wirst", "wo", "wollen", "wollte", "würde", "würden", "zu", "zum", "zur", "zwar"};
std::vector<Word> stop_words;
for_each(begin(stops),end(stops),[&](std::string stop){
	Word word{stop};
	stop_words.push_back(word);
});
//TODO: another loop to push german words in? Or selective push depending on the language
return stop_words;
}

void prepareContainers(std::vector<Word>& vec,std::set<Word>& set,
		std::multiset<Word>& multiset, std::multimap<const int, Word>& map){
for_each(begin(vec),end(vec),[&](Word word){
	set.insert(word);
	multiset.insert(word);
});

for_each(begin(set),end(set),[&](Word word){
	map.insert({multiset.count(word),word});
});
}

void prepareContainers_stopFiltered(std::vector<Word>& vec,std::set<Word>& set,
		std::multiset<Word>& multiset, std::multimap<const int, Word>& map){
std::vector<Word> stop_words = getStopWordsAll();
for_each(begin(vec),end(vec),[&](Word word){
	if(std::find(begin(stop_words),end(stop_words),word) == stop_words.end()){
		set.insert(word);
		multiset.insert(word);
	}
});

for_each(begin(set),end(set),[&](Word word){
	map.insert({multiset.count(word),word});
});
}

int wcount(std::istream& in){
std::vector<Word> vec = buildVector(in);
return vec.size();
}

int wdiffcount(std::istream& in){
std::vector<Word> vec = buildVector(in);
std::set<Word> set;
for_each(begin(vec),end(vec),[&](Word word){
	set.insert(word);
});
return set.size();
}

void wfavorite(std::ostream& out, std::istream& in){
std::vector<Word> vec = buildVector(in);
std::set<Word> set{};
std::multiset<Word> multiset{};
std::multimap<const int,Word> map{};

prepareContainers(vec,set,multiset,map);

int limit = 20;
for_each(rbegin(map),rend(map),[&](std::pair<const int,Word> p){
	if(limit >= 0){
	Word myword = p.second;
	out <<  myword << ":" << p.first << "\n";
	limit--;
	}else{
		return;
	}
});
}

void wordle(std::ostream& out, std::istream& in){
std::vector<Word> vec = buildVector(in);
std::set<Word> set{};
std::multiset<Word> multiset{};
std::multimap<const int,Word> map{};

prepareContainers_stopFiltered(vec,set,multiset,map);

int limit = 20;
for_each(rbegin(map),rend(map),[&](std::pair<const int,Word> p){
	if(limit >= 0){
	Word myword = p.second;
	out <<  myword << ":" << p.first << "\n";
	limit--;
	}else{
		return;
	}
});
}

















