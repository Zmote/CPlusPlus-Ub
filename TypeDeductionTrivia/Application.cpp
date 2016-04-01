#include "Trivia.h"
#include "QuestionGenerator.h"
#include <iostream>




int main(int argc, char **argv) {
	auto questions = createQuestions();
	trivia(std::cout, std::cin, questions);
//	printAll(std::cout, questions);
}

