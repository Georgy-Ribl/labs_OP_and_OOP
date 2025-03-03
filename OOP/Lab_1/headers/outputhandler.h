#ifndef OUTPUTHANDLER_H
#define OUTPUTHANDLER_H

#include <string>

class OutputHandler {
public:
    void printMessage(const std::string &message) const;
    void printError(const std::string &errorMessage) const;
};

#endif // OUTPUTHANDLER_H
