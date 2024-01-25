#include "physics.h"
#include "utilities.h"
#include "shape.h"
#include <iostream>
#include <unordered_map>

b2World* world; 
std::unordered_map<b2Body*, std::shared_ptr<Shape>> bodyShapeMap;

void stepPhysics() {
    world->Step(simulationFrameRate, velocityIteration, positionIteration);
}

void initStaticGround() {
    world = new b2World(b2Vec2(0.0, gravity));

    // Bucket dimensions
    float bucketWidth = pixels2Meters(WIDTH / 2);
    float bucketHeight = pixels2Meters(50);
    float wallThickness = pixels2Meters(20);    

    // Create a static body for the bucket
    b2BodyDef bucketBodyDef;

    int bucketOffset = 100;
    float bucketCenterX = pixels2Meters(WIDTH / 2); 
    float bucketCenterY = pixels2Meters(HEIGHT - bucketHeight / 2 - bucketOffset);
    bucketBodyDef.position.Set(bucketCenterX, bucketCenterY);
    
    b2Body* bucketBody = world->CreateBody(&bucketBodyDef);
    b2PolygonShape bottomShape;
    bottomShape.SetAsBox(bucketWidth / 2, wallThickness / 2, b2Vec2(0, bucketHeight / 2), 0);
    bucketBody->CreateFixture(&bottomShape, 0.0f);
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

    // Create and initialize a new shape and associate the shape with the body in a map
    ShapeFactory factory;
    std::shared_ptr<Shape> square = factory.createShape("Square");
    square->init("../shaders/vertex_shader.glsl", "../shaders/fragment_shader_red.glsl");
    bodyShapeMap[body] = square;

    return body;
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

        shape->update(glm::vec2(meters2Pixels(position.x), meters2Pixels(position.y)), angle);
        shape->render();
    }

}

