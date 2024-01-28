#ifndef SHAPE_H
#define SHAPE_H

#include "utilities.h"
#include <memory>
#include <string>
#include <glm/glm.hpp>          // The main GLM header
#include <glm/gtc/type_ptr.hpp>  // For glm::value_ptr
#include <vector>

//TODO: Update to use indexing 

class Shape {
public:
    virtual void init(std::string, std::string) = 0;
    virtual void update(const glm::vec2&, float) = 0; 
    virtual void render() = 0;
    virtual void useShaderProg() = 0;
    virtual void draw() = 0;
    virtual void generateCircleVertices() { };
    
    virtual void setWidthHeight(int, int) { };
    virtual void setRadius(int) { };
    virtual std::vector<std::string> getBinding() { };
    
    virtual ~Shape() = default;
};

class Square : public Shape {
private:
    float vertices[18] = {
        -0.5f,  0.5f, 0.0f, 
         0.5f,  0.5f, 0.0f, 
        -0.5f, -0.5f, 0.0f, 

         0.5f,  0.5f, 0.0f, 
         0.5f, -0.5f, 0.0f, 
        -0.5f, -0.5f, 0.0f  
    };

    int width;
    int height;    
    unsigned int VBO;
    unsigned int VAO;
    unsigned int shaderProgram;
    glm::mat4 transformationMatrix;

public:
    void setWidthHeight(int, int) override;
    void init(std::string, std::string) override;
    void update(const glm::vec2&, float) override;
    void render() override;
    void useShaderProg() override;
    void draw() override;
};

class Ground : public Shape {
private:

    float vertices[234] = {
        0.540000f, 0.772202f, 0.0f,
        0.532000f, 0.082202f, 0.0f,
        0.888000f, -0.002798f, 0.0f,
        0.540000f, 0.772202f, 0.0f,
        0.888000f, -0.002798f, 0.0f,
        0.888000f, 0.772202f, 0.0f,
        0.532000f, 0.082202f, 0.0f,
        0.488000f, -0.087798f, 0.0f,
        0.452000f, -0.665298f, 0.0f,
        0.532000f, 0.082202f, 0.0f,
        0.452000f, -0.665298f, 0.0f,
        0.624000f, -0.535297f, 0.0f,
        0.532000f, 0.082202f, 0.0f,
        0.624000f, -0.535297f, 0.0f,
        0.748000f, -0.387798f, 0.0f,
        0.532000f, 0.082202f, 0.0f,
        0.748000f, -0.387798f, 0.0f,
        0.848000f, -0.185298f, 0.0f,
        0.532000f, 0.082202f, 0.0f,
        0.848000f, -0.185298f, 0.0f,
        0.888000f, -0.002798f, 0.0f,
        -0.540000f, 0.772202f, 0.0f,
        -0.888000f, 0.772202f, 0.0f,
        -0.884000f, -0.002798f, 0.0f,
        -0.540000f, 0.772202f, 0.0f,
        -0.884000f, -0.002798f, 0.0f,
        -0.540000f, 0.079702f, 0.0f,
        -0.540000f, 0.079702f, 0.0f,
        -0.884000f, -0.002798f, 0.0f,
        -0.848000f, -0.187798f, 0.0f,
        -0.540000f, 0.079702f, 0.0f,
        -0.848000f, -0.187798f, 0.0f,
        -0.764000f, -0.355297f, 0.0f,
        -0.540000f, 0.079702f, 0.0f,
        -0.764000f, -0.355297f, 0.0f,
        -0.480000f, -0.120298f, 0.0f,
        -0.480000f, -0.120298f, 0.0f,
        -0.764000f, -0.355297f, 0.0f,
        -0.652000f, -0.507798f, 0.0f,
        -0.480000f, -0.120298f, 0.0f,
        -0.652000f, -0.507798f, 0.0f,
        -0.524000f, -0.620297f, 0.0f,
        -0.480000f, -0.120298f, 0.0f,
        -0.524000f, -0.620297f, 0.0f,
        -0.328000f, -0.727798f, 0.0f,
        -0.480000f, -0.120298f, 0.0f,
        -0.328000f, -0.727798f, 0.0f,
        -0.172000f, -0.772798f, 0.0f,
        -0.480000f, -0.120298f, 0.0f,
        -0.172000f, -0.772798f, 0.0f,
        -0.380000f, -0.252798f, 0.0f,
        0.452000f, -0.665298f, 0.0f,
        0.488000f, -0.087798f, 0.0f,
        0.452000f, -0.165297f, 0.0f,
        0.452000f, -0.665298f, 0.0f,
        0.452000f, -0.165297f, 0.0f,
        0.248000f, -0.755298f, 0.0f,
        -0.172000f, -0.772798f, 0.0f,
        0.112000f, -0.772798f, 0.0f,
        0.248000f, -0.755298f, 0.0f,
        -0.172000f, -0.772798f, 0.0f,
        0.248000f, -0.755298f, 0.0f,
        -0.380000f, -0.252798f, 0.0f,
        0.452000f, -0.165297f, 0.0f,
        0.328000f, -0.297797f, 0.0f,
        0.248000f, -0.755298f, 0.0f,
        0.328000f, -0.297797f, 0.0f,
        0.180000f, -0.377798f, 0.0f,
        0.248000f, -0.755298f, 0.0f,
        0.180000f, -0.377798f, 0.0f,
        0.064000f, -0.405297f, 0.0f,
        0.248000f, -0.755298f, 0.0f,
        0.064000f, -0.405297f, 0.0f,
        -0.148000f, -0.387798f, 0.0f,
        0.248000f, -0.755298f, 0.0f,
        -0.148000f, -0.387798f, 0.0f,
        -0.276000f, -0.332798f, 0.0f,
        0.248000f, -0.755298f, 0.0f
    };

    std::vector<std::string> groundBounding = {
        "135.0000, 308.8810 , 133.0000, 32.8810 , 222.0000, -1.1190 , 222.0000, 308.8810",
        "133.0000, 32.8810 , 122.0000, -35.1190 , 113.0000, -266.1190 , 156.0000, -214.1190 , 187.0000, -155.1190 , 212.0000, -74.1190 , 222.0000, -1.1190",
        "-135.0000, 308.8810 , -222.0000, 308.8810 , -221.0000, -1.1190 , -135.0000, 31.8810",
        "-135.0000, 31.8810 , -221.0000, -1.1190 , -212.0000, -75.1190 , -191.0000, -142.1190 , -120.0000, -48.1190",
        "-120.0000, -48.1190 , -191.0000, -142.1190 , -163.0000, -203.1190 , -131.0000, -248.1190 , -82.0000, -291.1190 , -43.0000, -309.1190 , -95.0000, -101.11902",
        "113.0000, -266.1190 , 122.0000, -35.1190 , 113.0000, -66.1190 , 62.0000, -302.1190",
        "-43.0000, -309.1190 , 28.0000, -309.1190 , 62.0000, -302.1190 , -95.0000, -101.1190",
        "113.0000, -66.1190 , 82.0000, -119.1190 , 62.0000, -302.1190",
        "82.0000, -119.1190 , 45.0000, -151.1190 , 62.0000, -302.1190",
        "45.0000, -151.1190 , 16.0000, -162.1190 , 62.0000, -302.1190",
        "16.0000, -162.1190 , -37.0000, -155.1190 , 62.0000, -302.1190",
        "-37.0000, -155.1190 , -69.0000, -133.1190 , 62.0000, -302.1190"
    };

    int width;
    int height;    
    unsigned int VBO;
    unsigned int VAO;
    unsigned int shaderProgram;
    glm::mat4 transformationMatrix;

public:
    void setWidthHeight(int, int) override;
    void init(std::string, std::string) override;
    void update(const glm::vec2&, float) override;
    void render() override;
    void useShaderProg() override;
    void draw() override;

    std::vector<std::string> getBinding() override {
        return groundBounding;
    }
};

class ShapeFactory {
public:
    std::shared_ptr<Shape> createShape(const std::string& shapeType);
};

class Circle : public Shape {
private:

    //float vertices[10] = {
    //    1.0f, 0.0f, 0.0f,
    //    -0.5f, 0.866f, 0.0f,
    //    -0.5f, -0.866f, 0.0f
    //};

    static const int vertexCount = 30; // 36 vertices for a smoother circle
    float vertices[vertexCount * 3] = {}; // 3 components (x, y, z) per vertex
    int radius;
    unsigned int VBO;
    unsigned int VAO;
    unsigned int shaderProgram;
    glm::mat4 transformationMatrix;

public:
    void init(std::string, std::string) override;
    void update(const glm::vec2&, float) override;
    void render() override;
    void useShaderProg() override;
    void draw() override;

    void setRadius(int r) override {
        radius = r;
    }

    void generateCircleVertices() override {
        for (int i = 0; i < vertexCount; ++i) {
            float angle = 2.0f * M_PI * float(i) / float(vertexCount);

            vertices[i * 3] = radius * cos(angle);
            vertices[i * 3 + 1] = radius * sin(angle);      // y-coordinate
            vertices[i * 3 + 2] = 0.0f;                     // z-coordinate
        }
    }
};

#endif // SHAPE_H
