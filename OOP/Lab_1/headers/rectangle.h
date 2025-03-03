#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "figure.h"
#include <stdexcept>

class Rectangle : public Figure {
private:
    std::string name;
    double x1;
    double y1;
    double x2;
    double y2;

public:
    Rectangle(const std::string &nameVal,
              double leftX, double topY,
              double rightX, double bottomY);

    double getArea() const override;
    void printParameters() const override;
};

#endif // RECTANGLE_H
