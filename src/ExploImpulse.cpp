#include "ExploImpulse.h"


void ExploImpulse::explode(Particle* A, Vector explosionCenter, float explosionRadius, float explosionForce){
	Vector explosionVector = A->getPosition() - explosionCenter;
	float distance = explosionVector.norm();
	// Impulsion
	Vector initialVelocity = A->getVelocity();
	Vector direction = explosionVector.normalize() * explosionForce * (1 - distance / explosionRadius);
	A->setVelocity(initialVelocity + direction);
}
