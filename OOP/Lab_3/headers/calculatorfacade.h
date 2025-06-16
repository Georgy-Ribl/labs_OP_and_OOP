#ifndef CALCULATOR_FACADE_H
#define CALCULATOR_FACADE_H

#include "CalculatorEngine.h"
#include "Command.h"
#include <vector>
#include <memory>

class CalculatorFacade {
    CalculatorEngine engine;
    std::string currentExpr;
    double lastResult{0.0};
    double memory{0.0};

    std::vector<std::unique_ptr<ICommand>> history;
    size_t historyPos{0};

public:
    void input(const std::string& in);
    void evaluate();
    void undo();
    void redo();
    void memoryAdd();
    void memorySub();
    void memoryRecall();
    void memoryClear();

    void rawInput(const std::string& in);
    void rawDel();

    const std::string& getExpression() const { return currentExpr; }

    void _setExpression(const std::string& e) { currentExpr = e; }
    const std::string& _getExpression() const { return currentExpr; }
    void _setLastResult(double v) { lastResult = v; }
    double _getLastResult() const { return lastResult; }
    void _setMemory(double v) { memory = v; }
    double _getMemory() const { return memory; }

private:
    void _pushHistory(std::unique_ptr<ICommand> cmd);
};

#endif // CALCULATOR_FACADE_H
