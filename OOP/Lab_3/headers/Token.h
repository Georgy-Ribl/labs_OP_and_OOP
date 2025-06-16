#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    Number,
    Operator,
    LeftParen,
    RightParen,
    Function
};

class Token {
public:
    Token(TokenType type = TokenType::Number, const std::string &text = "");

    TokenType getType() const;
    const std::string& getText() const;

    void setType(TokenType type);
    void setText(const std::string &text);

private:
    TokenType   type_;
    std::string text_;
};

#endif // TOKEN_H
