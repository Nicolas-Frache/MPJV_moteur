#pragma once
#include "Vector.h"
#include "Force.h"
class ConstantForce: public Force {
	public :
		float mass;

		ConstantForce(Particle* particle_, Vector direction_);
		Vector ConstantForce::value() override;
		void ConstantForce::updateForce(Particle* particle, float duration) override;
		float ConstantForce::updateTimeElapsed(float time) override;
};