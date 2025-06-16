#include "CalculatorEngine.h"
#include "tokenizer.h"
#include <stack>
#include <memory>
#include <cmath>
#include <stdexcept>

static double factorial(double v) {
    if (v < 0) throw std::runtime_error("Factorial of negative");
    unsigned long long n = static_cast<unsigned long long>(std::floor(v + 0.5));
    double res = 1;
    for (unsigned long long i = 2; i <= n; ++i) res *= i;
    return res;
}

static double safeCtg(double v) {
    double t = std::tan(v);
    if (std::fabs(t) < 1e-12) {
        throw std::runtime_error("Error");
    }
    return 1.0 / t;
}

std::vector<Token> CalculatorEngine::toRPN(const std::vector<Token>& tokens) const {
    std::vector<Token> out;
    std::stack<Token> ops;
    for (const auto& t : tokens) {
        switch (t.getType()) {
        case TokenType::Number:
            out.push_back(t);
            break;
        case TokenType::Function:
            ops.push(t);
            break;
        case TokenType::Operator:
            while (!ops.empty() &&
                   ((ops.top().getType() == TokenType::Operator &&
                     ((isLeftAssociative(t.getText()) && precedence(t.getText()) <= precedence(ops.top().getText())) ||
                      (!isLeftAssociative(t.getText()) && precedence(t.getText()) <  precedence(ops.top().getText()))))
                    || ops.top().getType() == TokenType::Function)) {
                out.push_back(ops.top());
                ops.pop();
            }
            ops.push(t);
            break;
        case TokenType::LeftParen:
            ops.push(t);
            break;
        case TokenType::RightParen:
            while (!ops.empty() && ops.top().getType() != TokenType::LeftParen) {
                out.push_back(ops.top());
                ops.pop();
            }
            if (ops.empty()) throw std::runtime_error("Mismatched parentheses");
            ops.pop();
            if (!ops.empty() && ops.top().getType() == TokenType::Function) {
                out.push_back(ops.top());
                ops.pop();
            }
            break;
        }
    }
    while (!ops.empty()) {
        if (ops.top().getType() == TokenType::LeftParen ||
            ops.top().getType() == TokenType::RightParen)
            throw std::runtime_error("Mismatched parentheses");
        out.push_back(ops.top());
        ops.pop();
    }
    return out;
}

double CalculatorEngine::evalRPN(const std::vector<Token>& rpn) const {
    std::stack<std::unique_ptr<double>> st;
    for (const auto& t : rpn) {
        if (t.getType() == TokenType::Number) {
            st.push(std::make_unique<double>(std::stod(t.getText())));
        }
        else if (t.getType() == TokenType::Operator) {
            if (t.getText() == "!") {
                if (st.empty()) throw std::runtime_error("Invalid '!'");
                double a = *st.top(); st.pop();
                st.push(std::make_unique<double>(factorial(a)));
            } else {
                if (st.size() < 2) throw std::runtime_error("Invalid expression");
                double b = *st.top(); st.pop();
                double a = *st.top(); st.pop();
                double r = 0;
                const auto& op = t.getText();
                if      (op == "+") r = a + b;
                else if (op == "-") r = a - b;
                else if (op == "*") r = a * b;
                else if (op == "/") r = a / b;
                else if (op == "^") r = std::pow(a, b);
                st.push(std::make_unique<double>(r));
            }
        }
        else {
            if (st.empty()) throw std::runtime_error("Invalid function");
            double v = *st.top(); st.pop();
            double r = 0;
            const auto& fn = t.getText();
            if      (fn == "sqrt") r = std::sqrt(v);
            else if (fn == "sin")  r = std::sin(v);
            else if (fn == "cos")  r = std::cos(v);
            else if (fn == "tg")   r = std::tan(v);
            else if (fn == "ctg") {
                double s = std::sin(v);
                if (std::fabs(s) < 1e-12)
                    throw std::runtime_error("Division by zero in ctg");
                r = std::cos(v) / s;
            }
            else if (fn == "ln")   r = std::log(v);
            else if (fn == "log")  r = std::log10(v);
            else throw std::runtime_error("Unknown function: " + fn);
            st.push(std::make_unique<double>(r));
        }
    }
    if (st.size() != 1) throw std::runtime_error("Invalid expression");
    return *st.top();
}

double CalculatorEngine::evaluate(const std::string& expression) {
    auto toks = tokenizer.tokenize(expression);
    auto rpn  = toRPN(toks);
    return evalRPN(rpn);
}

int CalculatorEngine::precedence(const std::string& op) const {
    if      (op == "!") return 5;
    else if (op == "^") return 4;
    else if (op == "*" || op == "/") return 3;
    else if (op == "+" || op == "-") return 2;
    return 0;
}

bool CalculatorEngine::isLeftAssociative(const std::string& op) const {
    return !(op == "^" || op == "!");
}
