#pragma once
#include "ParticleForceGenerator.h"
class Gravity : public ParticleForceGenerator {
private:
	Vector gravity = Vector(0, -9.8, 0);
	
	bool updateForce(Particle* particle, float duration) override {
		// F = m * g
		particle->addForce(gravity * particle->getMass());
		// Pas de temps d'application sur la gravité
		return true;
	}
};

