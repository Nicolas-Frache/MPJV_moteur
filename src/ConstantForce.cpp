#include "ConstantForce.h"
//cette sous classe sera principalement les forces genre gravit�

ConstantForce::ConstantForce(Particle* particle_, Vector direction_) : Force(particle_, direction_, 0) {
	mass = particle_->getMass();
}

Vector ConstantForce::value() { //une force constante style F = m * g (d'o� l'acc�l�ration g)
	return direction * mass;
}

void ConstantForce::updateForce(Particle* particle, float duration) {
	 return; // Il n'y a rien � faire, la force est constante
}

float ConstantForce::updateTimeElapsed(float time) {
	updateForce(particle, time);
	return time;
}
