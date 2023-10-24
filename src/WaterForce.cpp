#include "WaterForce.h"

WaterForce::WaterForce(Particle* A, float waterDensity, float waterDragCoef, float duration) : Force(A, duration) {
	_waterDensity = waterDensity;
	_waterDragCoef = waterDragCoef;
}

Vector WaterForce::value() {
	return direction;
}

void WaterForce::updateForce(Particle* particle, float duration) {
	if (!particle) {
		return;
	}

	Vector velocity = particle->getVelocity();
	float speed = velocity.norm();
	float dragMagnitude = _waterDensity * speed * speed * _waterDragCoef;
	
	Vector dragDirection = -velocity.normalize();

	Vector waterDragForce = dragDirection * dragMagnitude;

	direction = waterDragForce;
}