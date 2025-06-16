#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "Token.h"
#include <vector>
#include <string>

class Tokenizer {
public:
    std::vector<Token> tokenize(const std::string& expr) const;
};

#endif // TOKENIZER_H
