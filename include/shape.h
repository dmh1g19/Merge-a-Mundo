#ifndef SHAPE_H
#define SHAPE_H

#include <memory>
#include <string>
#include <glm/glm.hpp>          // The main GLM header
#include <glm/gtc/matrix_transform.hpp>  // For glm::translate, glm::rotate, glm::scale
#include <glm/gtc/type_ptr.hpp>  // For glm::value_ptr


class Shape {
public:
    virtual void init(int, int, std::string, std::string) = 0;
    virtual void update(const glm::vec2&, float) = 0; 
    virtual void render() = 0;
    virtual ~Shape() = default;
};

class Square : public Shape {
private:
    // Static vertex data for a square centered at the origin
    // this is needed to populate the shader matrix transformation 
    // otherwise any trasformation is applied to the null matrix
    // weird OpenGL things, the object is commonly initialized
    // at the center fo the screen

    float vertices[18] = {
        -0.5f,  0.5f, 0.0f, 
         0.5f,  0.5f, 0.0f, 
        -0.5f, -0.5f, 0.0f, 

         0.5f,  0.5f, 0.0f, 
         0.5f, -0.5f, 0.0f, 
        -0.5f, -0.5f, 0.0f  
    };

    unsigned int VBO;
    unsigned int VAO;
    unsigned int shaderProgram;
    glm::mat4 transformationMatrix;

public:
    void init(int, int, std::string, std::string) override;
    void update(const glm::vec2&, float) override;
    void render() override;
};

class ShapeFactory {
public:
    std::shared_ptr<Shape> createShape(const std::string& shapeType);
};

#endif // SHAPE_H
