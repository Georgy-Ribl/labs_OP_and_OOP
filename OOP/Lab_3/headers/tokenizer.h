#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <string>
#include "Token.h"

class Tokenizer {
public:
    std::vector<Token> tokenize(const std::string &expr) const;
};

#endif // TOKENIZER_H
