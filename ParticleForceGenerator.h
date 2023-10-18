#pragma once
#include "Particle.h"
#include "Vector.h"
class ParticleForceGenerator
{
	public :
		virtual void updateForce(Particle* particle, float duree);

};

