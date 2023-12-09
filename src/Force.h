#pragma once
#include "Vector.h"
#include "Particle.h"

class Particle; //déclaration anticipée de particle

class Force{
public:
	Vector direction = Vector(0, 0, 0);

	// Durée de l'application de la force en s
	float remainingTime;
	Particle* particle;

	Force(Particle* particle_, Vector direction_, float duration_);
	Force(Particle* particle_, float duration_);
	
	virtual float updateTimeElapsed(float time);

	virtual Vector value();

	//on va remplacer updateTimeElapsed et value par updateForce
	virtual void updateForce(Particle* particle, float duration);
};

