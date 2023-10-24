#include "DampingForce.h"

DampingForce::DampingForce(Particle* A, float dampingFactor) : Force(A, -1) {
	_dampingFactor = dampingFactor;
}

Vector DampingForce::value() {
	float dampX = -_dampingFactor * particle->getVelocity().x();
	float dampZ = -_dampingFactor * particle->getVelocity().z();
	
	return Vector(dampX, 0.f, dampZ); //force opposée à la vel de la particule
}
float DampingForce::updateTimeElapsed(float time) {
	updateForce(particle, time);
	return time;
}