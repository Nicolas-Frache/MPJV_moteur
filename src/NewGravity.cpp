#pragma once
#include "ParticleForceGenerator.cpp"

class Gravity : public ParticleForceGenerator {
public:
	Vector gravity = Vector(0, -9.8, 0);

	bool updateForce(Particle* particle, float duration) override {
		cout << "3  gravity update:   " << gravity << endl;

		// F = m * g
		particle->addForce(gravity * particle->getMass());
		// Pas de temps d'application sur la gravité
		return true;
	}
};

