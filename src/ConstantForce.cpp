#include "ConstantForce.h"

ConstantForce::ConstantForce(Vector direction_, float mass_, float duration_) : Force(direction_, duration_) {
	mass = mass_;
}

Vector ConstantForce::value() { //genre une force constante style F = m * g (d'où l'accélération g)
	return direction * mass;
}