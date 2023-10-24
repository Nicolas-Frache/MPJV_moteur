#include "ConstantForce.h"
//cette sous classe sera principalement les forces genre gravité

ConstantForce::ConstantForce(Particle* particle_, Vector direction_) : Force(particle_, direction_, 0) {
	mass = particle_->getMass();
}

Vector ConstantForce::value() { //une force constante style F = m * g (d'où l'accélération g)
	return direction * mass;
}

void ConstantForce::updateForce(Particle* particle, float duration) {
	if (!particle) {
		return;
	}
	Vector force = value();
	direction = force; //toujours constante donc on modif rien ici
}

float ConstantForce::updateTimeElapsed(float time) {
	updateForce(particle, time);
	return time;
}
