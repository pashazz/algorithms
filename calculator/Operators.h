//
// Created by Pasha on 31/12/2019.
//

#ifndef CALCULATOR_OPERATORS_H
#define CALCULATOR_OPERATORS_H

#include <cmath>
#include "Operator.h"






class Plus : public Operator {
public:
    int operatorPriority() const override {
        return 1;
    }
    double apply(double left, double right ) const override {
        return left + right;
    }

    std::string toString() const override {
        return "+";
    }

};

class Minus : public Operator {
public:
    int operatorPriority() const override {
        return 1;
    }
    double apply(double left, double right ) const override {
        return left - right;
    }

    std::string toString() const override {
        return "-";
    }

};

class Times : public Operator {
public:
    int operatorPriority() const override {
        return 2;
    }
    double apply(double left, double right ) const override {
        return left * right;
    }

    std::string toString() const override {
        return "*";
    }
};

class Division : public Operator {
public:
    int operatorPriority() const override  {
        return 2;
    }

    double apply(double left, double right ) const override {
        return left / right;
    }

    std::string toString() const override {
        return "/";
    }
};

class Power : public Operator {
public:
    int operatorPriority() const override  {
        return 3;
    }
    double apply(double left, double right)  const override  {
        return std::pow(left, right);
    }

    std::string toString() const override {
        return "^";
    }
};
#endif //CALCULATOR_OPERATORS_H
