#include "CalculatorFacade.h"
#include "InputCommand.h"
#include "EvaluateCommand.h"
#include "MemoryCommand.h"
#include <stdexcept>
#include <cmath>

void CalculatorFacade::rawInput(const std::string& in) {
    if (currentExpr == "Error") {
        if (in == "C" || in == "Del") {
            currentExpr.clear();
            return;
        }
        currentExpr.clear();
    }

    if (in == "C") {
        currentExpr.clear();
    }
    else if (in == "Del") {
        if (!currentExpr.empty())
            currentExpr.pop_back();
    }
    else {
        currentExpr += in;
    }
}

void CalculatorFacade::rawDel() {
    if (currentExpr == "Error" || currentExpr.empty()) {
        currentExpr.clear();
    } else {
        currentExpr.pop_back();
    }
}

void CalculatorFacade::input(const std::string& in) {
    auto cmd = std::make_unique<InputCommand>(*this, in);
    cmd->execute();
    _pushHistory(std::move(cmd));
}

void CalculatorFacade::evaluate() {
    try {
        double result = engine.evaluate(currentExpr);
        if (std::isinf(result) || std::isnan(result)) {
            currentExpr = "Error";
        } else {
            lastResult = result;
            currentExpr = std::to_string(result);
        }
    } catch (...) {
        currentExpr = "Error";
    }
}

void CalculatorFacade::memoryAdd() {
    try {
        double v = std::stod(currentExpr);
        memory += v;
    } catch (...) {}
}

void CalculatorFacade::memorySub() {
    try {
        double v = std::stod(currentExpr);
        memory -= v;
    } catch (...) {}
}

void CalculatorFacade::memoryRecall() {
    currentExpr = std::to_string(memory);
}

void CalculatorFacade::memoryClear() {
    memory = 0.0;
}

void CalculatorFacade::_pushHistory(std::unique_ptr<ICommand> cmd) {
    history.resize(historyPos);
    history.push_back(std::move(cmd));
    historyPos = history.size();
}
