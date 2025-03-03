#include "circle.h"
#include <iostream>
#include <cmath>

Circle::Circle(const std::string &nameVal, double x, double y, double r)
    : name(nameVal), centerX(x), centerY(y), radius(r)
{
    if (r <= 0.0) {
        throw std::invalid_argument("Circle radius must be positive.");
    }
}

double Circle::getArea() const {
    return M_PI * radius * radius;
}

void Circle::printParameters() const {
    std::cout << "Circle \"" << name
              << "\" Center=(" << centerX << ", " << centerY
              << "), Radius=" << radius << std::endl;
}
