#include "shapeFactory.h"
#include <memory>
#include <iostream>

std::shared_ptr<Shape> ShapeFactory::createShape(const std::string& shapeType) {
    if (shapeType == "Square") {
        return std::make_unique<Square>();
    }
    else if (shapeType == "Ground") {
        return std::make_unique<Ground>();
    }
    else if (shapeType == "Circle") {
        return std::make_unique<Circle>();
    }
    else {
        std::cout << "Unknown shape type" << std::endl;
        return nullptr; // Return nullptr to indicate an unknown shape type.
    }
}
