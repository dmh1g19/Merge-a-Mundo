#include "rendering.h"
#include <iostream>
#include <fstream>
#include <sstream>

/* 1 - Generating and Binding a VAO, 
   2 - Generating and Binding a VBO,
   3 - Setting Vertex Data in VBO, 
   4 - Configuring Vertex Attributes,
   5 - Draw the shape.
*/

std::string readShaderFromFile(std::string& filePath) {
    std::string shaderCode;
    std::ifstream shaderFile;

    // Ensure ifstream objects can throw exceptions
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        shaderFile.open(filePath);

        // Read file's buffer contents into streams
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        shaderCode = shaderStream.str();
    } catch (std::ifstream::failure& e) {
        std::cerr << "Error: Failed to read shader file: " << e.what() << std::endl;
    }

    return shaderCode;
}

void initBuffers(unsigned int& VBO, unsigned int& VAO, float vertices[], size_t verticesSize) {
    // Generate and bind the Vertex Array Object first
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind the Vertex Buffer Object
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Allocate memory and initialize data for VBO
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind the VAO to prevent accidental modification (not strictly necessary but good practice)
    glBindVertexArray(0);

    std::cout << "1 - Initialized VAO and VBO" << std::endl;
}

unsigned int initVertexShader(std::string& path) {
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Attach the shader source code to the shader object and compile the shader
    std::string vertexShaderCode = readShaderFromFile(path);
    const char* vertexShaderSource = vertexShaderCode.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    else {
        std::cout << "2 - Initialized vertex shader" << std::endl;
    }

    return vertexShader;
}

// For calculating the colour
unsigned int initFragmentShader(std::string& path) {
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string fragmentShaderCode = readShaderFromFile(path);
    const char* fragmentShaderSource = fragmentShaderCode.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    int success;
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    else {
        std::cout << "3 - Initialized fragment shader" << std::endl;
    }

    return fragmentShader;
}

unsigned int linkShaders(unsigned int vertexShader, unsigned int fragmentShader) {
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();    

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINKER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    else {
        std::cout << "4 - Linked vertex and fragment shaders (program object made)" << std::endl;
        std::cout << "  - every rendering call will use this program object" << std::endl;
    }

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);  

    return shaderProgram;
}

void drawShape(unsigned int shaderProgram, unsigned int VAO, int minVertices, int maxVertices) {
    glUseProgram(shaderProgram);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, minVertices, maxVertices);
    glBindVertexArray(0);

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << err << std::endl;
    }

    //std::cout << "6 - Drew shape" << std::endl;
}
