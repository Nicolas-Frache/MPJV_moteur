#pragma once
#include "Vector.h"
#include "Force.h"
class ConstantForce: public Force {
	public :
		float mass;

		ConstantForce(Vector direction_,float mass, float duration_);
		Vector ConstantForce::value() override;
};