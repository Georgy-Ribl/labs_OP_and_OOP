#include "Command.h"
#include "CalculatorFacade.h"

InputCommand::InputCommand(CalculatorFacade& f, const std::string& in)
    : facade(f), input(in) {}

void InputCommand::execute() {
    facade.rawInput(input);
}

void InputCommand::undo() {
    facade.rawDel();
}

EvaluateCommand::EvaluateCommand(CalculatorFacade& f) : facade(f) {}

void EvaluateCommand::execute() {
    prevExpr = facade._getExpression();
    facade.evaluate();
}

void EvaluateCommand::undo() {
    facade._setExpression(prevExpr);
}

MemoryCommand::MemoryCommand(CalculatorFacade& f, Op op)
    : facade(f), operation(op), prevMemory(f._getMemory()) {}

void MemoryCommand::execute() {
    switch (operation) {
    case Op::Add:    facade.memoryAdd();    break;
    case Op::Sub:    facade.memorySub();    break;
    case Op::Recall: facade.memoryRecall(); break;
    case Op::Clear:  facade.memoryClear();  break;
    }
}

void MemoryCommand::undo() {
    facade._setMemory(prevMemory);
}
