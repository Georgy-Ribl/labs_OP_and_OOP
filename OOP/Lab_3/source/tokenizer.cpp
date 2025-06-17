#include "tokenizer.h"
#include <cctype>
#include <stdexcept>

std::vector<Token> Tokenizer::tokenize(const std::string &expr) const {
    std::vector<Token> tokens;
    size_t i = 0;
    while (i < expr.size()) {
        if (std::isspace(expr[i])) { ++i; continue; }

        if (std::isdigit(expr[i]) || expr[i] == '.') {
            int dots = (expr[i]=='.');
            size_t start = i++;
            while (i < expr.size() && (std::isdigit(expr[i]) || expr[i]=='.')) {
                if (expr[i]=='.' && ++dots > 1)
                    throw std::runtime_error("Invalid number format");
                ++i;
            }
            tokens.emplace_back(TokenType::Number,
                                expr.substr(start, i - start));
            continue;
        }

        char c = expr[i++];
        switch (c) {
        case '+': case '-': case '*': case '/':
        case '^':
            tokens.emplace_back(TokenType::Operator,
                                std::string(1, c));
            break;
        case '(':
            tokens.emplace_back(TokenType::LeftParen, "(");
            break;
        case ')':
            tokens.emplace_back(TokenType::RightParen, ")");
            break;
        default:
            throw std::runtime_error(std::string("Invalid char: ") + c);
        }
    }
    return tokens;
}
