//
// Created by Pasha on 30/12/2019.
//

#ifndef CALCULATOR_PARSEREXCEPTION_H
#define CALCULATOR_PARSEREXCEPTION_H

#include <exception>

class ParserException : public std::exception {
public:
    ParserException(std::size_t pos, const std::string &what)
    {
        msg = new char[what.size() + 20];
        snprintf(msg, what.size() + 20, "Parser error at char %lu: %s", pos, what.c_str());
    }
    ~ParserException() {
        delete[] msg;
    }
    [[nodiscard]] const char* what() const _NOEXCEPT override {
        return msg;
    }

private:
    char *msg;
    size_t pos;

};


#endif //CALCULATOR_PARSEREXCEPTION_H
