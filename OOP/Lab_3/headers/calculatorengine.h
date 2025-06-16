#ifndef CALCULATOR_ENGINE_H
#define CALCULATOR_ENGINE_H

#include <string>
#include <vector>
#include <stack>
#include <memory>
#include <stdexcept>

enum class TokenType { Number, Operator, LeftParen, RightParen, Function };

class Number {
public:
    virtual ~Number() = default;
    virtual double value() const = 0;
};

class ConcreteNumber : public Number {
    double val;
public:
    explicit ConcreteNumber(double v);
    double value() const override;
};

struct Token {
    TokenType type;
    std::string text;
};

class CalculatorEngine {
public:
    double evaluate(const std::string& expression);
private:
    std::vector<Token> tokenize(const std::string& expr);
    std::vector<Token> toRPN(const std::vector<Token>& tokens);
    double evalRPN(const std::vector<Token>& rpn);
    int precedence(const std::string& op) const;
    bool isLeftAssociative(const std::string& op) const;
};

#endif // CALCULATOR_ENGINE_H
