#ifndef EVALUATECOMMAND_H
#define EVALUATECOMMAND_H

#include "ICommand.h"
#include <string>

class CalculatorFacade;

class EvaluateCommand : public ICommand {
    CalculatorFacade& facade;
    std::string prevExpr;
public:
    explicit EvaluateCommand(CalculatorFacade& f);
    void execute() override;
    void undo()    override;
};

#endif // EVALUATECOMMAND_H
