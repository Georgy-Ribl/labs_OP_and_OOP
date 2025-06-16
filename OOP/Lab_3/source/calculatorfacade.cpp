#include "CalculatorFacade.h"
#include <stdexcept>

void CalculatorFacade::rawInput(const std::string& in) {
    if (in == "C") {
        currentExpr.clear();
        return;
    }
    if (in == "Del") {
        if (!currentExpr.empty()) currentExpr.pop_back();
        return;
    }
    currentExpr += in;
}

void CalculatorFacade::rawDel() {
    if (!currentExpr.empty()) currentExpr.pop_back();
}

void CalculatorFacade::input(const std::string& in) {
    auto cmd = std::make_unique<InputCommand>(*this, in);
    cmd->execute();
    _pushHistory(std::move(cmd));
}

void CalculatorFacade::evaluate() {
    lastResult = engine.evaluate(currentExpr);
    currentExpr = std::to_string(lastResult);
}

void CalculatorFacade::undo() {
    if (historyPos == 0) return;
    historyPos--;
    history[historyPos]->undo();
}

void CalculatorFacade::redo() {
    if (historyPos >= history.size()) return;
    history[historyPos]->execute();
    historyPos++;
}

void CalculatorFacade::memoryAdd() {
    double v = std::stod(currentExpr);
    memory += v;
}
void CalculatorFacade::memorySub() {
    double v = std::stod(currentExpr);
    memory -= v;
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
