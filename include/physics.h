#ifndef PHYSICS_H
#define PHYSICS_H

/* dependent on window as the physics is based on window the frame rate and size */

#include "window.h"
#include "shape.h"
#include <box2d/box2d.h>
#include <memory>

extern b2World* world;

const float M2P = 20;
const float P2M = 1 / M2P;

const float simulationFrameRate = 1.0 / framesPerSecond;
const float dynamicBodyDensity = 1.0;

const int velocityIteration = 8;
const int positionIteration = 3;
const int gravity = 9.81;

void initStaticGround();
void stepPhysics();
void renderScene();

b2Body* addRect(int, int, int, int, bool);

#endif // PHYSICS_H