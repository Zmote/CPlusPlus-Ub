
#ifndef QUESTION_H_
#define QUESTION_H_

#include <string>


struct Question
{
    Question(std::string callingCode, std::string calledCode, std::string typeT, std::string typeParamType);
    bool checkTypeT(std::string const & answer) const;
    bool checkTypeP(std::string const & answer) const;

    std::string const callingCode;
    std::string const calledCode;
    std::string const typeT;
    std::string const typeParamType;
};



#endif /* QUESTION_H_ */
