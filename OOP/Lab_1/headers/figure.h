#ifndef FIGURE_H
#define FIGURE_H

#include <string>

class Figure {
public:
    virtual ~Figure() {}
    virtual double getArea() const = 0;
    virtual void printParameters() const = 0;
};

#endif // FIGURE_H
