#include "physics.h"
#include "utilities.h"
#include "shapeFactory.h"
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <vector>

b2World* world; 
ShapeFactory factory;
std::unordered_map<b2Body*, std::shared_ptr<Shape>> bodyShapeMap;

void stepPhysics() {
    world->Step(simulationFrameRate, velocityIteration, positionIteration);
}

void addStaticGround(int x, int y, int w, int h, bool dyn, const std::vector<std::string>& polygonData) {
    world = new b2World(b2Vec2(0.0f, gravity));

    b2BodyDef bodyDef;
    if (dyn) {
        bodyDef.type = b2_dynamicBody;
    } else {
        bodyDef.type = b2_staticBody;
    }
    bodyDef.position.Set(pixels2Meters(x), pixels2Meters(y));
    bodyDef.angle = b2_pi; // Rotate the body by 180 degrees

    b2Body* body = world->CreateBody(&bodyDef);

    // Add the polygons from PhysicsEditor
    for (const auto& polyCoords : polygonData) {
        std::vector<b2Vec2> vertices = parsePolygonCoordinates(polyCoords);

        b2PolygonShape polygonShape;
        polygonShape.Set(vertices.data(), vertices.size());

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &polygonShape;
        body->CreateFixture(&fixtureDef);
    }

    std::shared_ptr<Shape> ground = factory.createShape("Ground");
    ground->setWidthHeight(w, h);
    addToMap(ground, body, "../shaders/vertex_shader_ground.glsl", "../shaders/fragment_shader_ground.glsl");
}

void addRect(int x, int y, int w, int h, bool dyn) {
    std::cout << "\nMade rectangle at " + std::to_string(x) + ", " + std::to_string(y) << std::endl;

    b2BodyDef bodyDef;
    bodyDef.position.Set(pixels2Meters(x), pixels2Meters(y));
    if (dyn) {
        bodyDef.type = b2_dynamicBody;
    } else {
        bodyDef.type = b2_staticBody;
    }
    b2Body* body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(pixels2Meters(w/2), pixels2Meters(h/2));

    b2FixtureDef fixturedef;
    fixturedef.shape = &shape;
    fixturedef.density = dynamicBodyDensity; 
    body->CreateFixture(&fixturedef);

    std::shared_ptr<Shape> square = factory.createShape("Square");
    square->setWidthHeight(w, h);
    addToMap(square, body, "../shaders/vertex_shader_square.glsl", "../shaders/fragment_shader_square.glsl");
}

void addCircle(int x, int y, int radius, bool dyn) {
    std::cout << "\nMade circle at " + std::to_string(x) + ", " + std::to_string(y) << std::endl;

    b2BodyDef bodydef;
    bodydef.position.Set(pixels2Meters(x), pixels2Meters(y));
    if (dyn) {
        bodydef.type = b2_dynamicBody;
    }
    b2Body* body = world->CreateBody(&bodydef);

    b2CircleShape shape;
    shape.m_radius = pixels2Meters(radius*radius); // Multiply by 2 to get circumference

    b2FixtureDef fixturedef;
    fixturedef.shape = &shape;
    fixturedef.density = dynamicBodyDensity; 
    body->CreateFixture(&fixturedef);

    std::shared_ptr<Shape> circle = factory.createShape("Circle");
    circle->setRadius(radius);
    circle->generateCircleVertices();
    addToMap(circle, body, "../shaders/vertex_shader_circle.glsl", "../shaders/fragment_shader_circle.glsl");
}

// Associate the shape with the body in a map, this baically adds the object to the world 
void addToMap(std::shared_ptr<Shape> object, b2Body* body, std::string vertexShader, std::string fragmentShader) {
    object->init(vertexShader, fragmentShader);
    bodyShapeMap[body] = object;
}

// Draw all the objects in the scene after associating the box2d objects with the opengl shapes
void renderScene() {
    // Clear the screen
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Iterate over the bodyShapeMap
    // Update shape's position and rotation
    for (const auto& pair : bodyShapeMap) {
        b2Body* body = pair.first;
        std::shared_ptr<Shape> shape = pair.second;

        const b2Vec2& position = body->GetPosition();
        float angle = body->GetAngle();

        shape->useShaderProg();
        shape->update(glm::vec2(meters2Pixels(position.x), meters2Pixels(position.y)), angle/-1); // Have to invert the angle for opengl
        shape->render();
        shape->draw();
    }

}
