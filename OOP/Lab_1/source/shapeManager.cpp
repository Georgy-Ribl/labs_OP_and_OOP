#include "shapeManager.h"
#include <iostream>
#include <algorithm>

void ShapeManager::addShape(std::unique_ptr<Figure> shape) {
    shapes.push_back(std::move(shape));
}

void ShapeManager::printAllParameters() const {
    if (shapes.empty()) {
        std::cout << "No shapes in the collection." << std::endl;
        return;
    }
    for (size_t i = 0; i < shapes.size(); ++i) {
        std::cout << (i + 1) << ". ";
        shapes[i]->printParameters();
    }
}

void ShapeManager::printAllAreas() const {
    if (shapes.empty()) {
        std::cout << "No shapes in the collection." << std::endl;
        return;
    }
    for (size_t i = 0; i < shapes.size(); ++i) {
        double area = shapes[i]->getArea();
        std::cout << (i + 1) << ". Area = " << area << std::endl;
    }
}

void ShapeManager::printSumOfAreas() const {
    double sum = 0.0;
    for (const auto &shape : shapes) {
        sum += shape->getArea();
    }
    std::cout << "Sum of all areas = " << sum << std::endl;
}

void ShapeManager::sortByAreaAscending() {
    std::sort(shapes.begin(), shapes.end(),
              [](const std::unique_ptr<Figure> &a,
                 const std::unique_ptr<Figure> &b)
              {
                  return a->getArea() < b->getArea();
              });
}

bool ShapeManager::removeByIndex(size_t index) {
    if (index == 0 || index > shapes.size()) {
        return false;
    }
    shapes.erase(shapes.begin() + (index - 1));
    return true;
}

void ShapeManager::removeIfAreaGreaterThan(double limit) {
    shapes.erase(
        std::remove_if(
            shapes.begin(),
            shapes.end(),
            [limit](const std::unique_ptr<Figure> &ptr){
                return ptr->getArea() > limit;
            }
            ),
        shapes.end()
        );
}
