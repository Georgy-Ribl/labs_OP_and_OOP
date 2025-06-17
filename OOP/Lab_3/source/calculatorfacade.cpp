#include "CalculatorFacade.h"
#include <cmath>
#include <stdexcept>

void CalculatorFacade::rawInput(const std::string &in) {
    if (currentExpr_ == "Error") {
        currentExpr_.clear();
    }
    if (in == "C") {
        currentExpr_.clear();
    } else if (in == "Del") {
        if (!currentExpr_.empty())
            currentExpr_.pop_back();
    } else {
        currentExpr_ += in;
    }
}

void CalculatorFacade::input(const std::string &in) {
    rawInput(in);
}

void CalculatorFacade::evaluate() {
    try {
        double r = engine_.evaluate(currentExpr_);
        if (std::isnan(r) || std::isinf(r))
            currentExpr_ = "Error";
        else
            currentExpr_ = std::to_string(r);
    } catch (...) {
        currentExpr_ = "Error";
    }
}

const std::string& CalculatorFacade::getExpression() const {
    return currentExpr_;
}
