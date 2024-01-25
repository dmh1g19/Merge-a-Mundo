#include "physics.h"
#include "utilities.h"
#include "shape.h"
#include <iostream>
#include <unordered_map>

b2World* world; 
ShapeFactory factory;
std::unordered_map<b2Body*, std::shared_ptr<Shape>> bodyShapeMap;

void stepPhysics() {
    world->Step(simulationFrameRate, velocityIteration, positionIteration);
}

void initStaticGround(int x, int y, int w, int h, bool dyn) {
    world = new b2World(b2Vec2(0.0, gravity));

    b2BodyDef bodyDef;
    bodyDef.position.Set(pixels2Meters(x), pixels2Meters(y));
    b2Body* body = world->CreateBody(&bodyDef);

    b2PolygonShape bottomShape;
    bottomShape.SetAsBox(pixels2Meters(w / 2), pixels2Meters(h / 2));
    body->CreateFixture(&bottomShape, 0.0f);

    std::shared_ptr<Shape> ground = factory.createShape("Ground");
    addToMap(ground, body, "../shaders/vertex_shader.glsl");
}

b2Body* addRect(int x, int y, int w, int h, bool dyn) {
    std::cout << "\nMade rectangle at " + std::to_string(x) + ", " + std::to_string(y) << std::endl;

    b2BodyDef bodydef;
    bodydef.position.Set(pixels2Meters(x), pixels2Meters(y));
    if (dyn) {
        bodydef.type = b2_dynamicBody;
    }
    b2Body* body = world->CreateBody(&bodydef);

    b2PolygonShape shape;
    shape.SetAsBox(pixels2Meters(w / 2), pixels2Meters(h / 2));

    b2FixtureDef fixturedef;
    fixturedef.shape = &shape;
    fixturedef.density = dynamicBodyDensity; 
    body->CreateFixture(&fixturedef);

    std::shared_ptr<Shape> square = factory.createShape("Square");
    addToMap(square, body, "../shaders/vertex_shader.glsl");

    return body;
}

// Associate the shape with the body in a map this essentially adds the object to the world 
void addToMap(std::shared_ptr<Shape> object, b2Body* body, std::string vertexShader) {
    // TODO: dynamically add shaders, perhaps through a shader class

    object->init(vertexShader, "../shaders/fragment_shader_red.glsl");
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

        shape->update(glm::vec2(meters2Pixels(position.x), meters2Pixels(position.y)), angle/-1); // Have to invert the angle for some reason
        shape->render();
    }

}

