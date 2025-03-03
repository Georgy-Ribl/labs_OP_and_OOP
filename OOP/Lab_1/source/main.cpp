#include <iostream>
#include <memory>
#include "shapeManager.h"
#include "inputHandler.h"
#include "outputHandler.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"

static void printMenu() {
    std::cout << "\nMenu:\n"
              << "1. Add Circle\n"
              << "2. Add Rectangle\n"
              << "3. Add Triangle\n"
              << "4. Print list of figures (type & parameters)\n"
              << "5. Print list of figures (type & area)\n"
              << "6. Print sum of all areas\n"
              << "7. Sort figures by area ascending\n"
              << "8. Remove figure by index\n"
              << "9. Remove figures with area > user value\n"
              << "0. Exit\n"
              << "Enter your choice: ";
}

static bool handleMenuChoice(int choice,
                             ShapeManager &manager,
                             InputHandler &input,
                             OutputHandler &output)
{
    if (choice == 0) {
        return false;
    }

    if (choice == 1) {

        std::string name = input.getString("Enter circle name: ");
        double x = input.getDouble("Enter center X: ");
        double y = input.getDouble("Enter center Y: ");
        double r = input.getDouble("Enter radius: ");
        try {
            auto circle = std::make_unique<Circle>(name, x, y, r);
            manager.addShape(std::move(circle));
            output.printMessage("Circle added successfully.");
        } catch (const std::exception &ex) {
            output.printError(ex.what());
        }
    } else if (choice == 2) {

        std::string name = input.getString("Enter rectangle name: ");
        double leftX = input.getDouble("Enter left X: ");
        double topY = input.getDouble("Enter top Y: ");
        double rightX = input.getDouble("Enter right X: ");
        double bottomY = input.getDouble("Enter bottom Y: ");
        try {
            auto rect = std::make_unique<Rectangle>(name, leftX, topY, rightX, bottomY);
            manager.addShape(std::move(rect));
            output.printMessage("Rectangle added successfully.");
        } catch (const std::exception &ex) {
            output.printError(ex.what());
        }
    } else if (choice == 3) {
        std::string name = input.getString("Enter triangle name: ");
        double x1 = input.getDouble("Enter x1: ");
        double y1 = input.getDouble("Enter y1: ");
        double x2 = input.getDouble("Enter x2: ");
        double y2 = input.getDouble("Enter y2: ");
        double x3 = input.getDouble("Enter x3: ");
        double y3 = input.getDouble("Enter y3: ");
        try {
            auto tri = std::make_unique<Triangle>(name, x1, y1, x2, y2, x3, y3);
            manager.addShape(std::move(tri));
            output.printMessage("Triangle added successfully.");
        } catch (const std::exception &ex) {
            output.printError(ex.what());
        }
    } else if (choice == 4) {
        manager.printAllParameters();
    } else if (choice == 5) {
        manager.printAllAreas();
    } else if (choice == 6) {
        manager.printSumOfAreas();
    } else if (choice == 7) {
        manager.sortByAreaAscending();
        output.printMessage("Shapes sorted by area.");
    } else if (choice == 8) {
        int idx = input.getInt("Enter index of shape to remove: ");
        if (manager.removeByIndex(static_cast<size_t>(idx))) {
            output.printMessage("Shape removed.");
        } else {
            output.printError("Invalid index.");
        }
    } else if (choice == 9) {
        double limit = input.getDouble("Enter area limit: ");
        manager.removeIfAreaGreaterThan(limit);
        output.printMessage("Shapes removed if area > limit.");
    } else {
        output.printError("Unknown menu option.");
    }
    return true;
}

int main()
{
    ShapeManager manager;
    InputHandler input;
    OutputHandler output;
    bool running = true;

    while (running) {
        printMenu();
        int choice = input.getInt("");
        running = handleMenuChoice(choice, manager, input, output);
    }
    return 0;
}
