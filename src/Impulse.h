#pragma once

#include "Particle.h"
#include "Vector.h"

class Impulse
{
	public:
		Impulse(Particle* object1, Particle* object2, Vector impactPoint);
		Impulse(Particle* object1, Particle* object2);

};

