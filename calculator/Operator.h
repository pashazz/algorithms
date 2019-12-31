//
// Created by Pasha on 31/12/2019.
//

#ifndef CALCULATOR_OPERATOR_H
#define CALCULATOR_OPERATOR_H

#include <exception>


class NotAnOperatorException : public std::exception {
    [[nodiscard]] const char* what() const _NOEXCEPT override {
        return "Not an operator";
    }
};

class Operator  {
public:
    virtual ~Operator() {}
    virtual int operatorPriority() const  = 0;
    virtual double apply(double left, double right) const = 0;
    virtual std::string toString() const = 0;
};

class LeftBracket : public Operator {
public:
    virtual int operatorPriority() const override { //This is a special value for left bracket.
        return 0;
    }


    virtual double apply(double left, double right) const override {
        assert(false);
    }

    std::string toString() const override {
        return "(";
    }
};


#endif //CALCULATOR_OPERATOR_H
