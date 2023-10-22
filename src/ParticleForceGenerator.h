#pragma once
#include "Particle.h"
class ParticleForceGenerator
{
private:
	float durationRemaining;

public:
	/** applique la force sur une particule donn�e pour une frame
	* 
	* @param particule la particule sur laquelle appliquer la force
	* @param duration la dur�e de la frame
	* @return false si la force est arriv� � la fin de son temps d'application, true sinon
	*/
	virtual bool updateForce(Particle* particule, float duration) = 0;
};

