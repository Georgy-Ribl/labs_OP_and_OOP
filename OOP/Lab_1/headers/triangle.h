#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "figure.h"
#include <stdexcept>

class Triangle : public Figure {
private:
    std::string name;
    double x1, y1;
    double x2, y2;
    double x3, y3;

public:
    Triangle(const std::string &nameVal,
             double x1Val, double y1Val,
             double x2Val, double y2Val,
             double x3Val, double y3Val);

    double getArea() const override;
    void printParameters() const override;
};

#endif // TRIANGLE_H
