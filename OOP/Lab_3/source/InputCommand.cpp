#include "InputCommand.h"
#include "CalculatorFacade.h"

InputCommand::InputCommand(CalculatorFacade& f, const std::string& in)
    : facade(f), input(in) {}

void InputCommand::execute() {
    facade.rawInput(input);
}

void InputCommand::undo() {
    facade.rawDel();
}
