#pragma once
#include "Particle.h"
class ParticleForceGenerator
{
private:
	float durationRemaining = 0;

public:
	/** applique la force sur une particule donnée pour une frame
	* 
	* @param particule la particule sur laquelle appliquer la force
	* @param duration la durée de la frame
	* @return false si la force est arrivée à la fin de son temps d'application, true sinon
	*/
	virtual bool updateForce(Particle* particule, float duration) = 0;
};

