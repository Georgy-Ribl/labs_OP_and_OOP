#ifndef CALCULATORFACADE_H
#define CALCULATORFACADE_H

#include <string>
#include "CalculatorEngine.h"

class CalculatorFacade {
public:
    void input(const std::string &in);
    void evaluate();
    const std::string& getExpression() const;

private:
    void rawInput(const std::string &in);
    std::string currentExpr_;
    CalculatorEngine engine_;
};

#endif // CALCULATORFACADE_H
