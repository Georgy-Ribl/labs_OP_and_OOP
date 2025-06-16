#ifndef INPUTCOMMAND_H
#define INPUTCOMMAND_H

#include "ICommand.h"
#include <string>

class CalculatorFacade;

class InputCommand : public ICommand {
    CalculatorFacade& facade;
    std::string input;
public:
    InputCommand(CalculatorFacade& f, const std::string& in);
    void execute() override;
    void undo()    override;
};

#endif // INPUTCOMMAND_H
