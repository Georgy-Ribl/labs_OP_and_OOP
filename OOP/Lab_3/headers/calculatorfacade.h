#ifndef CALCULATORFACADE_H
#define CALCULATORFACADE_H

#include <string>
#include <vector>
#include <memory>
#include "CalculatorEngine.h"
#include "ICommand.h"

class CalculatorFacade {
    CalculatorEngine engine;
    std::string currentExpr;
    double lastResult{0.0}, memory{0.0};
    std::vector<std::unique_ptr<ICommand>> history;
    size_t historyPos{0};

public:
    void input(const std::string& in);
    void evaluate();
    void memoryAdd();
    void memorySub();
    void memoryRecall();
    void memoryClear();

    void rawInput(const std::string& in);
    void rawDel();

    const std::string& getExpression() const { return currentExpr; }

    void _setExpression(const std::string& e) { currentExpr = e; }
    const std::string& _getExpression() const { return currentExpr; }
    void _setMemory(double v) { memory = v; }
    double _getMemory() const { return memory; }

private:
    void _pushHistory(std::unique_ptr<ICommand> cmd);
};

#endif // CALCULATORFACADE_H
