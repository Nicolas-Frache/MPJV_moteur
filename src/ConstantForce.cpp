#include "ConstantForce.h"
//cette sous classe sera principalement les forces genre gravité
//sinon bah Force(vecteur_force) suffit

ConstantForce::ConstantForce(Particle* particle_, Vector direction_, float mass_, float duration_) : Force(particle_, direction_, duration_) {
	mass = mass_;
}

Vector ConstantForce::value() { //genre une force constante style F = m * g (d'où l'accélération g)
	return direction * mass;
}

void ConstantForce::updateForce(Particle* particle, float duration) {
	if (!particle) {
		return;
	}
	Vector force = value();
	direction = force; //toujours constante donc on modif rien ici
}

float ConstantForce::updateTimeElapsed(float time)
{
	updateForce(particle, time);
	if (timeRemaining - time > 0) {
		timeRemaining -= time;
		return time;
	}
	return timeRemaining;
}
