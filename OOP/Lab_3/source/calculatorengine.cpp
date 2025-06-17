#include "CalculatorEngine.h"
#include "tokenizer.h"
#include <stack>
#include <memory>
#include <cmath>
#include <stdexcept>

std::vector<Token> CalculatorEngine::insertImplicitMultiplication(const std::vector<Token>& tokens) const {
    std::vector<Token> out;
    for (size_t i = 0; i < tokens.size(); ++i) {
        out.push_back(tokens[i]);
        if (i + 1 < tokens.size()) {
            TokenType cur = tokens[i].getType();
            TokenType nxt = tokens[i + 1].getType();
            if ((cur == TokenType::Number || cur == TokenType::RightParen) &&
                (nxt == TokenType::LeftParen || nxt == TokenType::Number))
            {
                out.emplace_back(TokenType::Operator, "*");
            }
        }
    }
    return out;
}

std::vector<Token> CalculatorEngine::toRPN(const std::vector<Token>& origTokens) const {
    auto tokens = insertImplicitMultiplication(origTokens);
    std::vector<Token> output;
    std::stack<Token> ops;

    for (const auto& t : tokens) {
        switch (t.getType()) {
        case TokenType::Number:
            output.push_back(t);
            break;

        case TokenType::Operator: {
            std::string op = t.getText();
            while (!ops.empty() && ops.top().getType() == TokenType::Operator) {
                std::string topOp = ops.top().getText();
                bool cond = (isLeftAssociative(op) && precedence(op) <= precedence(topOp))
                            || (!isLeftAssociative(op) && precedence(op) <  precedence(topOp));
                if (!cond) break;
                output.push_back(ops.top());
                ops.pop();
            }
            ops.push(t);
            break;
        }

        case TokenType::LeftParen:
            ops.push(t);
            break;

        case TokenType::RightParen:
            while (!ops.empty() && ops.top().getType() != TokenType::LeftParen) {
                output.push_back(ops.top());
                ops.pop();
            }
            if (ops.empty()) throw std::runtime_error("Mismatched parentheses");
            ops.pop();
            break;
        }
    }

    while (!ops.empty()) {
        if (ops.top().getType() == TokenType::LeftParen ||
            ops.top().getType() == TokenType::RightParen) {
            throw std::runtime_error("Mismatched parentheses");
        }
        output.push_back(ops.top());
        ops.pop();
    }

    return output;
}

double CalculatorEngine::evalRPN(const std::vector<Token>& rpn) const {
    std::stack<std::unique_ptr<double>> st;

    for (const auto& t : rpn) {
        if (t.getType() == TokenType::Number) {
            st.push(std::make_unique<double>(std::stod(t.getText())));
        }
        else {
            std::string op = t.getText();
            if (st.size() < 2) throw std::runtime_error("Invalid expression");
            double b = *st.top(); st.pop();
            double a = *st.top(); st.pop();
            double r = 0;
            if      (op == "+") r = a + b;
            else if (op == "-") r = a - b;
            else if (op == "*") r = a * b;
            else if (op == "/") r = a / b;
            else if (op == "^") r = std::pow(a, b);
            else throw std::runtime_error("Unknown operator: " + op);
            st.push(std::make_unique<double>(r));
        }
    }

    if (st.size() != 1) throw std::runtime_error("Invalid expression");
    return *st.top();
}

double CalculatorEngine::evaluate(const std::string& expression) {
    auto tokens = tokenizer_.tokenize(expression);
    auto rpn    = toRPN(tokens);
    return evalRPN(rpn);
}

int CalculatorEngine::precedence(const std::string& op) const {
    if      (op == "^") return 4;
    else if (op == "*" || op == "/") return 3;
    else if (op == "+" || op == "-") return 2;
    return 0;
}

bool CalculatorEngine::isLeftAssociative(const std::string& op) const {
    return (op != "^");
}
