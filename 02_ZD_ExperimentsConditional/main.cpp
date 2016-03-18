#include <iostream>

int main() {
    bool cond{};
    std::cout << (cond ? "Hello" : "Peter");
}

/*
 * What happens is that std::cout outputs 0 or 1 (depending on the value of cond) rather
 * then outputting "Hello" or "Peter".
 * Putting the statement into () solves the problem, because it probably evaluated the statement
 * on the right first, thus it is a available as a variable for the operator << to match to
 * a the corresponding << function.
 * --> else << operator tries to evaluate and match it with one of its overloaded functions
 * but the ternary variable is only determined at runtime, which is why it can't determine it
 * on compile time --> operator<<(ostream,int) or ostream, char) --> which in this case would be
 * something like operator<<(ostream, (cond? "Hello" : "Peter")); --> thus it can't determine
 * which type, and thus it doesn't know which overloaded function to call.
 * CLARIFY IN EXERCISE LESSONS
 * */
