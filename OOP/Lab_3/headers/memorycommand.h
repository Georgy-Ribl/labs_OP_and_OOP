#ifndef MEMORYCOMMAND_H
#define MEMORYCOMMAND_H

#include "ICommand.h"

class CalculatorFacade;

class MemoryCommand : public ICommand {
public:
    enum class Op { Add, Sub, Recall, Clear };
private:
    CalculatorFacade& facade;
    Op operation;
    double prevMemory;
public:
    MemoryCommand(CalculatorFacade& f, Op op);
    void execute() override;
    void undo()    override;
};

#endif // MEMORYCOMMAND_H
