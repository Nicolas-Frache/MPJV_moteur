#include "ElastForce.h"

ElastForce::ElastForce(Particle* particle_, Particle* base_, float maxLength_, float springConstant_, float duration_) :
	Force(particle_, duration_),
	_base(base_),
	maxLength(maxLength_),
	springConstant(springConstant_)
{
}

Vector ElastForce::value()
{
	return direction;
}

void ElastForce::updateForce(Particle* particle, float duration)
{
	if (!particle) {
		return;
	}
	Vector elastVector = particle->getPosition() - _base->getPosition();
	float distance = elastVector.norm();

	if (distance > maxLength) {
		Vector springForce = elastVector;
		springForce.normalize();

		float forceMagnitude = -springConstant * (distance - maxLength);
		springForce *= forceMagnitude;

		direction = springForce;
	}
}

float ElastForce::updateTimeElapsed(float time)
{
	updateForce(particle, time);
	if (timeRemaining - time > 0) {
		timeRemaining -= time;
		return time;
	}
	return timeRemaining;
}