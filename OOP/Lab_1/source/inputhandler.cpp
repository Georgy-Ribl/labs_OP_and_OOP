#include "inputHandler.h"
#include <iostream>
#include <limits>

int InputHandler::getInt(const std::string &prompt) {
    int value = 0;
    bool valid = false;
    while (!valid) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid integer. Try again.\n";
        } else {
            valid = true;
        }
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

double InputHandler::getDouble(const std::string &prompt) {
    double value = 0.0;
    bool valid = false;
    while (!valid) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid double. Try again.\n";
        } else {
            valid = true;
        }
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

std::string InputHandler::getString(const std::string &prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return value;
}
