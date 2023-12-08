#include "ConstantForce.h"

//cette sous classe servira � appliquer une force constante � une particule, comme la gravit�

ConstantForce::ConstantForce(Particle* particle_, Vector direction_) : Force(particle_, direction_, 0) {}

Vector ConstantForce::value() { //une force constante style F = m * g (d'o� l'acc�l�ration g)
	return direction * particle->getMass();
}

void ConstantForce::updateForce(Particle* particle, float duration) {
	 return; // Il n'y a rien � faire, la force est constante
}

float ConstantForce::updateTimeElapsed(float time) {
	updateForce(particle, time);
	return time;
}
