#include "outputHandler.h"
#include <iostream>

void OutputHandler::printMessage(const std::string &message) const {
    std::cout << message << std::endl;
}

void OutputHandler::printError(const std::string &errorMessage) const {
    std::cerr << "Error: " << errorMessage << std::endl;
}
