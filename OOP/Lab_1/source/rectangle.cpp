#include "rectangle.h"
#include <iostream>
#include <cmath>

Rectangle::Rectangle(const std::string &nameVal,
                     double leftX, double topY,
                     double rightX, double bottomY)
    : name(nameVal), x1(leftX), y1(topY), x2(rightX), y2(bottomY)
{
    if (x2 <= x1) {
        throw std::invalid_argument("Invalid rectangle width (x2 <= x1).");
    }
    if (y2 >= y1) {
        throw std::invalid_argument("Invalid rectangle height (y2 >= y1).");
    }
}

double Rectangle::getArea() const {
    double width = x2 - x1;
    double height = y1 - y2;
    return width * height;
}

void Rectangle::printParameters() const {
    std::cout << "Rectangle \"" << name
              << "\" TopLeft=(" << x1 << ", " << y1
              << "), BottomRight=(" << x2 << ", " << y2 << ")"
              << std::endl;
}
