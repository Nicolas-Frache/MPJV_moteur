#include "Force.h"
#include <algorithm>

Force::Force(Particle* particle_, Vector direction_, float duration_){
	particle = particle_;
	direction = direction_;
	timeRemaining = duration_;
}

Force::Force(Particle* particle_, float duration_):
	Force::Force(particle_, Vector(0,0,0), duration_){
}

float Force::updateTimeElapsed(float time){
	updateForce(particle, time);
	if (timeRemaining - time > 0) {
		timeRemaining -= time;
		return time;
	}
	return timeRemaining;
}

Vector Force::value() { //permettra pour les sous-classes de Force de modifier la valeur de la force
	return direction;
}

void Force::updateForce(Particle* particle, float duration) {
	if (!particle) {
		return;
	}
	Vector force = value();
	direction = force; //dans les sous classes on modifiera ce vecteur force
}
