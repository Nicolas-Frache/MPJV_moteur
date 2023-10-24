#include "ExploForce.h"

ExploForce::ExploForce(Particle* A, Vector explosionCenter, float explosionRadius, float explosionForce) : Force(A, 1) {
	_explosionCenter = explosionCenter;
	_explosionRadius = explosionRadius;
	_explosionForce = explosionForce;
}

Vector ExploForce::value() {
	return direction;
}

void ExploForce::updateForce(Particle* particle, float duration) {
	if(!particle){
		return;
	}

	Vector explosionToParticle = particle->getPosition() - _explosionCenter;
	float distance = explosionToParticle.norm();

	if(distance < _explosionRadius){
		float force = _explosionForce * (1 - distance / _explosionRadius);
		direction = explosionToParticle.normalize() * force;
	}
}
