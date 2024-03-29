#ifndef PHYSICS_H
#define PHYSICS_H

/* dependent on window as the physics is based on window the frame rate and size */

#include "window.h"
#include "shapeFactory.h"
#include <box2d/box2d.h>
#include <memory>
#include <vector>
#include <string>

// Global pointer to the Box2D world
extern b2World* world;

const float simulationFrameRate = 1.0 / framesPerSecond;
const float dynamicBodyDensity = 1.0;

const int velocityIteration = 8;
const int positionIteration = 3;
const int gravity = 9.81;

void stepPhysics();
void renderScene();
void addToMap(std::shared_ptr<Shape>, b2Body*, std::string, std::string);

void addStaticGround(int, int, int, int, bool, const std::vector<std::string>&);
void addRect(int, int, int, int, bool);
void addCircle(int, int, int, bool);

std::vector<b2Vec2> parsePolygonCoordinates(const std::string&);

#endif // PHYSICS_H
