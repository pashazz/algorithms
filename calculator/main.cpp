#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>
#include <variant>

#include "Operator.h"
#include "ParserException.h"
#include "Operators.h"
using namespace std;

typedef variant<double, char> Token;

vector<Token> tokenize(const string &);

void pushAndClearCurrentNumber(string & currentNumber, const string & in, string::const_iterator  iter, vector<Token> & ret);

double calculate (const std::string &expr);

/**
 * Evaluates exception until an operator of lower precedence than priority is discovered in ops OR
 * or the op stack is empty
 *
 * The evaluated exception is at the top of the values stack
 */
void evaluate(stack<Operator*>&  ops, stack<double>& values, int priority);

int main() {
    //Get only one line
    string line = "(1+1)*3-(4-3)^2"; //2*3-1 = 5
    //string line = "2+2";
    //getline(cin, line);
    cout << line << endl;
    double val = calculate(line);
    cout << val << endl;



}
// Tokens: +, -, *, /, (, ), ^, number


double calculate(const std::string &expr) {
    vector<Token> stream = tokenize(expr);
    stack<Operator*> ops;
    stack<double> values;

        for (auto token : stream) {
        try {
            char c  = get<char>(token);
            std::cout <<  "calculate: operator: " << c << endl;
            Operator *oper;
            switch (c) {
                case '+':
                    oper = new Plus();
                    break;
                case '-':
                    oper = new Minus();
                    break;
                case '*':
                    oper = new Times();
                    break;
                case '/':
                    oper = new Division();
                    break;
                case '(':
                    oper = new LeftBracket();
                    break;
                case ')': //Make a number from everything until corresponding LeftBracket
                    evaluate(ops, values, 1);
                    assert(ops.top()->operatorPriority() == 0); // This is LeftBracket
                    ops.pop();
                    continue;
                case '^':
                    oper = new Power();
                    break;
                default:
                    assert(false);
            }
            if (c != '(') { //We'll call evaluate when the right bracket is there
                evaluate(ops, values, oper->operatorPriority());
            }
            ops.push(oper);

        }
        catch (const bad_variant_access&) {
            double value = get<double>(token);
            values.push(value);
            std::cout << "calculate: value: " << value << endl;
        }
    }
    // Evaluate leftovers
    evaluate(ops, values, 1);
    return values.top();
}

void evaluate(stack<Operator*> &ops, stack<double> &values, int priority) {
    while (!ops.empty() && ops.top()->operatorPriority() >= priority) {
        double rightValue = values.top();
        values.pop();
        double leftValue = values.top();
        values.pop();
        Operator *oper = ops.top();
        ops.pop();
        values.push(oper->apply(leftValue, rightValue));
        delete oper;
        cout << "evaluate: Push: " << leftValue << " " << oper->toString()  << " " << rightValue << " equals " << values.top() << endl;
    }c

}

bool lastTokenIsLeftBracketOrEmpty (const vector<Token>& ret, const std::string &currentNumber) {
    if (!currentNumber.empty()) {
        return false;
    }

    if (ret.size() == 0)
        return true;
    try {
        char token = get<char>(ret[ret.size() - 1]);
        if (token == '(')
            return true;
    } catch (const std::bad_variant_access &e) {

    }
    return false;
}

bool lastTokenIsRightBracket(const vector<Token> & ret, const std::string & currentNumber) {
    if (!currentNumber.empty()) {
        return false;
    }
    if (ret.size() == 0)
        return false;
    try {
        char token = get<char>(ret[ret.size() - 1]);
        if (token == ')')
            return true;
    } catch (const std::bad_variant_access &e) {

    }
    return false;
}

vector<Token> tokenize(const string &in) {
    string currentNumber;
    vector<Token> ret;
    int parDepth = 0;
    for(string::const_iterator iter = in.cbegin(); iter != in.cend(); ++iter) {
        if (isspace(*iter))
            continue;
        if (isdigit(*iter) ||
            (*iter == '-' && lastTokenIsLeftBracketOrEmpty(ret, currentNumber))) {
            currentNumber.push_back(*iter);
            continue;
        }
        switch (*iter) {
            case ')':
                if (parDepth == 0) {
                    throw ParserException(distance(in.cbegin(), iter), string("Unexpected: ), no matching ("));
                }
                parDepth--;
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                if (!lastTokenIsRightBracket(ret, currentNumber)) {
                    pushAndClearCurrentNumber(currentNumber, in, iter, ret);
                }
                ret.emplace_back(*iter);
                break;
            case '(': //Assume if we have something like 3(5+1) then it's 3*(5+1)
                if (!currentNumber.empty()) {
                    if (currentNumber[currentNumber.size() - 1] ==  '-') { // - (something) becomes -1*(something)
                        currentNumber.push_back('1');
                    }
                    pushAndClearCurrentNumber(currentNumber,in, iter, ret);
                    ret.emplace_back('*');
                }
                ret.emplace_back('(');
                parDepth++;
                break;
            default:
                throw ParserException(distance(in.cbegin(), iter), string("Unexpected token: ") + *iter);
        }
    }
    if (parDepth > 0) {
        ostringstream os;
        os << "There are ";
        os << parDepth;
        os << " unclosed parentheses";
        throw ParserException(distance(in.cbegin(), in.cend()), os.str());
    }

    if (!currentNumber.empty()) {
        pushAndClearCurrentNumber(currentNumber, in, --in.end(), ret);
    }
    return ret;
}

void pushAndClearCurrentNumber(string & currentNumber, const string & in, string::const_iterator iter, vector<Token> & ret) {
    if (currentNumber.empty() || currentNumber[currentNumber.size() - 1] == '-') {
        throw ParserException(distance(in.cbegin(), iter), string("Expected: number, got: ") + *iter);
    }
    istringstream is(currentNumber);
    double num;
    is >> num;
    ret.emplace_back(num);
    currentNumber.clear();
}


