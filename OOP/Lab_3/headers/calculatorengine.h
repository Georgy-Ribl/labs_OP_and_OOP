#ifndef CALCULATORENGINE_H
#define CALCULATORENGINE_H

#include <string>
#include <vector>
#include "Token.h"
#include "tokenizer.h"

class CalculatorEngine {
public:
    double evaluate(const std::string& expression);

private:
    std::vector<Token> toRPN(const std::vector<Token>& tokens) const;
    double evalRPN(const std::vector<Token>& rpn) const;
    int precedence(const std::string& op) const;
    bool isLeftAssociative(const std::string& op) const;

    std::vector<Token> insertImplicitMultiplication(const std::vector<Token>& tokens) const;

    Tokenizer tokenizer_;
};

#endif // CALCULATORENGINE_H
