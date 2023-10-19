#pragma once
#include "Particle.h"
#include "Vector.h"
#include "../ParticleForceGenerator.h"
class ParticleForceRegistry
{

	struct ParticleForceRegistration{
		Particle* particle;
		ParticleForceGenerator* fg;
	};

	typedef std::vector<ParticleForceRegistration> Registre;

	void add(Particle* particle, ParticleForceGenerator* fg);
	void remove(Particle* particle);
	void clear();
	void updateForces(float duration);


private:
	Registre registre;

	// Utilisez Vector pour stocker les forces au lieu de float
	Vector totalForce;

	// Utilisez Vector pour stocker la position précédente au lieu de float
	Vector previousPosition;

};

