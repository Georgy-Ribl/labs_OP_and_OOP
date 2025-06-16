#include "EvaluateCommand.h"
#include "CalculatorFacade.h"

EvaluateCommand::EvaluateCommand(CalculatorFacade& f) : facade(f) {}

void EvaluateCommand::execute() {
    prevExpr = facade._getExpression();
    facade.evaluate();
}

void EvaluateCommand::undo() {
    facade._setExpression(prevExpr);
}
