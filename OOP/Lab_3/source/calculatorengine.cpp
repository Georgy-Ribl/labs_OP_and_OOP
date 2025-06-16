#include "CalculatorEngine.h"
#include <cctype>
#include <cmath>
#include <algorithm>

// --- ConcreteNumber ---
ConcreteNumber::ConcreteNumber(double v) : val(v) {}
double ConcreteNumber::value() const { return val; }

// --- Tokenization ---
std::vector<Token> CalculatorEngine::tokenize(const std::string& expr) {
    std::vector<Token> tokens;
    size_t i = 0;
    while (i < expr.size()) {
        if (std::isspace(expr[i])) { ++i; continue; }
        // Number
        if (std::isdigit(expr[i]) || expr[i]=='.') {
            size_t s = i;
            while (i<expr.size() && (std::isdigit(expr[i])||expr[i]=='.')) ++i;
            tokens.push_back({TokenType::Number, expr.substr(s,i-s)});
            continue;
        }
        // Function or constant
        if (std::isalpha(expr[i])) {
            size_t s = i;
            while (i<expr.size() && std::isalpha(expr[i])) ++i;
            std::string name = expr.substr(s,i-s);
            std::transform(name.begin(), name.end(), name.begin(), ::tolower);
            if (name=="pi") {
                tokens.push_back({TokenType::Number, std::to_string(M_PI)});
            }
            else if (name=="e") {
                tokens.push_back({TokenType::Number, std::to_string(M_E)});
            }
            else {
                // normalize tg/tan, ctg/cot
                if (name=="tan"||name=="tg")  name="tg";
                if (name=="cot"||name=="ctg") name="ctg";
                tokens.push_back({TokenType::Function, name});
            }
            continue;
        }
        // Operator or parentheses
        char c = expr[i++];
        switch(c) {
        case '+': case '-': case '*': case '/':
        case '^': case '!':
            tokens.push_back({TokenType::Operator, std::string(1,c)});
            break;
        case '(': tokens.push_back({TokenType::LeftParen, "("}); break;
        case ')': tokens.push_back({TokenType::RightParen, ")"}); break;
        default:
            throw std::runtime_error(std::string("Invalid char: ")+c);
        }
    }
    return tokens;
}

// --- Precedence & associativity ---
int CalculatorEngine::precedence(const std::string& op) const {
    if (op=="!")            return 5;
    if (op=="^")            return 4;
    if (op=="*"||op=="/")   return 3;
    if (op=="+"||op=="-")   return 2;
    return 0;
}
bool CalculatorEngine::isLeftAssociative(const std::string& op) const {
    // ^ and ! are right-associative
    return !(op=="^" || op=="!");
}

// --- Shunting-yard → RPN ---
std::vector<Token> CalculatorEngine::toRPN(const std::vector<Token>& tokens) {
    std::vector<Token> out;
    std::stack<Token> ops;
    for (auto& t: tokens) {
        switch (t.type) {
        case TokenType::Number:
            out.push_back(t); break;
        case TokenType::Function:
            ops.push(t); break;
        case TokenType::Operator:
            while (!ops.empty() &&
                   ((ops.top().type==TokenType::Operator &&
                     ((isLeftAssociative(t.text) && precedence(t.text)<=precedence(ops.top().text)) ||
                      (!isLeftAssociative(t.text)&&precedence(t.text)<precedence(ops.top().text))))
                    || ops.top().type==TokenType::Function)) {
                out.push_back(ops.top()); ops.pop();
            }
            ops.push(t);
            break;
        case TokenType::LeftParen:
            ops.push(t); break;
        case TokenType::RightParen:
            while (!ops.empty() && ops.top().type!=TokenType::LeftParen) {
                out.push_back(ops.top()); ops.pop();
            }
            if (ops.empty()) throw std::runtime_error("Mismatched parentheses");
            ops.pop();
            if (!ops.empty() && ops.top().type==TokenType::Function) {
                out.push_back(ops.top()); ops.pop();
            }
            break;
        }
    }
    while (!ops.empty()) {
        if (ops.top().type==TokenType::LeftParen||ops.top().type==TokenType::RightParen)
            throw std::runtime_error("Mismatched parentheses");
        out.push_back(ops.top()); ops.pop();
    }
    return out;
}

// --- Factorial helper ---
static double factorial(double v) {
    if (v < 0) throw std::runtime_error("Factorial of negative");
    unsigned long long n = static_cast<unsigned long long>(std::floor(v+0.5));
    double res = 1;
    for (unsigned long long i = 2; i <= n; ++i) res *= i;
    return res;
}

// --- Evaluate RPN ---
double CalculatorEngine::evalRPN(const std::vector<Token>& rpn) {
    std::stack<std::unique_ptr<Number>> st;
    for (auto& t: rpn) {
        if (t.type==TokenType::Number) {
            st.push(std::make_unique<ConcreteNumber>(std::stod(t.text)));
        }
        else if (t.type==TokenType::Operator) {
            if (t.text=="!") {
                if (st.empty()) throw std::runtime_error("Invalid '!'");
                double a = st.top()->value(); st.pop();
                st.push(std::make_unique<ConcreteNumber>(factorial(a)));
            } else {
                if (st.size()<2) throw std::runtime_error("Invalid expression");
                double b = st.top()->value(); st.pop();
                double a = st.top()->value(); st.pop();
                double r = 0;
                if      (t.text=="+") r=a+b;
                else if (t.text=="-") r=a-b;
                else if (t.text=="*") r=a*b;
                else if (t.text=="/") r=a/b;
                else if (t.text=="^") r=std::pow(a,b);
                st.push(std::make_unique<ConcreteNumber>(r));
            }
        }
        else { // Function
            if (st.empty()) throw std::runtime_error("Invalid function");
            double v = st.top()->value(); st.pop();
            double r = 0;
            if      (t.text=="sqrt") r = std::sqrt(v);
            else if (t.text=="sin")  r = std::sin(v);
            else if (t.text=="cos")  r = std::cos(v);
            else if (t.text=="tg")   r = std::tan(v);
            else if (t.text=="ctg")  r = 1.0/std::tan(v);
            else if (t.text=="ln")   r = std::log(v);
            else if (t.text=="log")  r = std::log10(v);
            else throw std::runtime_error("Unknown function: "+t.text);
            st.push(std::make_unique<ConcreteNumber>(r));
        }
    }
    if (st.size()!=1) throw std::runtime_error("Invalid expression");
    return st.top()->value();
}

// --- Public entry ---
double CalculatorEngine::evaluate(const std::string& expression) {
    auto tokens = tokenize(expression);
    auto rpn    = toRPN(tokens);
    return evalRPN(rpn);
}
