/*
 * palindrom.h
 *
 *  Created on: 15.11.2015
 *      Author: Zmotions
 */

#ifndef PALINDROM_H_
#define PALINDROM_H_
#include <iosfwd>
#include <unordered_set>

bool is_palindrom(std::string input);
void printPalindromes_fromFile(std::ostream& out, std::string url);
void printPalindrome(std::ostream& out, std::string input);
std::unordered_set<std::string>  generate_anagrams(std::istream& in);
std::unordered_set<std::string> getValidWords(std::unordered_set<std::string> perumations);
void printAnagrams(std::ostream& out, std::unordered_set<std::string> myset);



#endif /* PALINDROM_H_ */
