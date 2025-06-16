#ifndef COMMAND_H
#define COMMAND_H

#include <string>

class CalculatorFacade;

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void execute() = 0;
    virtual void undo()    = 0;
};

class InputCommand : public ICommand {
    CalculatorFacade& facade;
    std::string input;
public:
    InputCommand(CalculatorFacade& f, const std::string& in);
    void execute() override;
    void undo()    override;
};

class EvaluateCommand : public ICommand {
    CalculatorFacade& facade;
    std::string prevExpr;
public:
    explicit EvaluateCommand(CalculatorFacade& f);
    void execute() override;
    void undo()    override;
};

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

#endif // COMMAND_H
