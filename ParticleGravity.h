#pragma once
#include "Particle.h"
#include "Vector.h"
#include "../ParticleForceGenerator.h"
#include "../ParticleForceRegistry.h"

class ParticleGravity : public ParticleForceGenerator
{

	public:
		Vector _gravity;
		ParticleGravity(Vector gravityVec);

		void updateForce(Particle* particle, float duree);

};

