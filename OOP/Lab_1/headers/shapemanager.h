#ifndef SHAPEMANAGER_H
#define SHAPEMANAGER_H

#include <vector>
#include <memory>
#include "figure.h"

class ShapeManager {
public:
    void addShape(std::unique_ptr<Figure> shape);
    void printAllParameters() const;
    void printAllAreas() const;
    void printSumOfAreas() const;
    void sortByAreaAscending();
    bool removeByIndex(size_t index);
    void removeIfAreaGreaterThan(double limit);

private:
    std::vector<std::unique_ptr<Figure>> shapes;
};

#endif // SHAPEMANAGER_H
