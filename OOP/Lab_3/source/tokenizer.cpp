#include "tokenizer.h"
#include "Token.h"
#include <cctype>
#include <algorithm>
#include <stdexcept>
#include <cmath>


std::vector<Token> Tokenizer::tokenize(const std::string& expr) const {
    std::vector<Token> tokens;
    size_t i = 0;
    while (i < expr.size()) {
        if (std::isspace(expr[i])) { ++i; continue; }

        if (std::isdigit(expr[i]) || expr[i] == '.') {
            int dotCount = 0;
            size_t start = i;
            if (expr[i] == '.') dotCount = 1;

            while (i < expr.size() && (std::isdigit(expr[i]) || expr[i] == '.')) {
                if (expr[i] == '.') {
                    dotCount++;
                    if (dotCount > 1) {
                        throw std::runtime_error("Invalid number format: multiple decimal points");
                    }
                }
                ++i;
            }
            tokens.emplace_back(TokenType::Number, expr.substr(start, i - start));
            continue;
        }

        if (std::isalpha(expr[i])) {
            size_t start = i;
            while (i < expr.size() && std::isalpha(expr[i])) ++i;
            std::string name = expr.substr(start, i - start);
            std::transform(name.begin(), name.end(), name.begin(), ::tolower);

            if (name == "pi") {
                tokens.emplace_back(TokenType::Number, std::to_string(M_PI));
            }
            else if (name == "e") {
                tokens.emplace_back(TokenType::Number, std::to_string(M_E));
            }
            else {
                if (name == "tg")  name = "tg";
                if (name == "ctg") name = "ctg";
                tokens.emplace_back(TokenType::Function, name);
            }
            continue;
        }

        char c = expr[i++];
        switch (c) {
        case '+': case '-': case '*': case '/':
        case '^': case '!':
            tokens.emplace_back(TokenType::Operator, std::string(1, c));
            break;
        case '(':
            tokens.emplace_back(TokenType::LeftParen, "(");
            break;
        case ')':
            tokens.emplace_back(TokenType::RightParen, ")");
            break;
        default:
            throw std::runtime_error(std::string("Invalid character: ") + c);
        }
    }
    return tokens;
}
