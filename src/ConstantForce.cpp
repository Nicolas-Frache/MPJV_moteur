#include "ConstantForce.h"

//cette sous classe servira à appliquer une force constante à une particule, comme la gravité

ConstantForce::ConstantForce(Particle* particle_, Vector direction_) : Force(particle_, direction_, 0) {}

Vector ConstantForce::value() { //une force constante style F = m * g (d'où l'accélération g)
	return direction * particle->getMass();
}

void ConstantForce::updateForce(Particle* particle, float duration) {
	 return; // Il n'y a rien à faire, la force est constante
}

float ConstantForce::updateTimeElapsed(float time) {
	updateForce(particle, time);
	return time;
}
