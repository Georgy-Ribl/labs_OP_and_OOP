#include "MemoryCommand.h"
#include "CalculatorFacade.h"

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
