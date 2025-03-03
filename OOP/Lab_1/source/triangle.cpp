#include "triangle.h"
#include <iostream>
#include <cmath>

static double computeTriangleArea(double x1, double y1,
                                  double x2, double y2,
                                  double x3, double y3)
{
    double area = std::fabs(
                      x1*(y2 - y3) +
                      x2*(y3 - y1) +
                      x3*(y1 - y2)
                      ) / 2.0;
    return area;
}

Triangle::Triangle(const std::string &nameVal,
                   double x1Val, double y1Val,
                   double x2Val, double y2Val,
                   double x3Val, double y3Val)
    : name(nameVal),
    x1(x1Val), y1(y1Val),
    x2(x2Val), y2(y2Val),
    x3(x3Val), y3(y3Val)
{
    double area = computeTriangleArea(x1, y1, x2, y2, x3, y3);
    const double EPSILON = 1e-9;
    if (area < EPSILON) {
        throw std::invalid_argument("Degenerate triangle (area is zero).");
    }
}

double Triangle::getArea() const {
    return computeTriangleArea(x1, y1, x2, y2, x3, y3);
}

void Triangle::printParameters() const {
    std::cout << "Triangle \"" << name
              << "\" Vertices=(" << x1 << ", " << y1 << "), "
              << "(" << x2 << ", " << y2 << "), "
              << "(" << x3 << ", " << y3 << ")"
              << std::endl;
}
