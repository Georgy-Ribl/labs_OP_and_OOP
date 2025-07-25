#include "Token.h"

Token::Token(TokenType type, const std::string &text)
    : type_(type), text_(text)
{}

TokenType Token::getType() const { return type_; }
const std::string& Token::getText() const { return text_; }

void Token::setType(TokenType t) { type_ = t; }
void Token::setText(const std::string &txt) { text_ = txt; }
