#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <string>

class InputHandler {
public:
    int getInt(const std::string &prompt);
    double getDouble(const std::string &prompt);
    std::string getString(const std::string &prompt);
};

#endif // INPUTHANDLER_H
