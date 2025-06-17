#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    Number,
    Operator,
    LeftParen,
    RightParen
};

class Token {
public:
    Token(TokenType type = TokenType::Number, const std::string &text = "");

    TokenType getType() const;
    const std::string& getText() const;

    void setType(TokenType t);
    void setText(const std::string &txt);

private:
    TokenType   type_;
    std::string text_;
};

#endif // TOKEN_H
