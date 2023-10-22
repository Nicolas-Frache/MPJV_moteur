#pragma once
#include "Ball.h"
#include "Vector.h"

class Cannonball : public Ball{


public:
    Cannonball(Vector position, float invertedMass, ofColor color, float size);
};
