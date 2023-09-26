#pragma once
#include "Particle.h"
#include "Vector.h"

class Laser : public Particle
{

public:
	Vector direction = Vector(1, 1, 1);

	Laser(Vector startPoint, Vector direction, float invertedMass, ofColor color, float size);


};

