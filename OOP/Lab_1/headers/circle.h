#ifndef CIRCLE_H
#define CIRCLE_H

#include "figure.h"
#include <stdexcept>

class Circle : public Figure {
private:
    std::string name;
    double centerX;
    double centerY;
    double radius;

public:
    Circle(const std::string &nameVal, double x, double y, double r);

    double getArea() const override;
    void printParameters() const override;
};

#endif // CIRCLE_H
