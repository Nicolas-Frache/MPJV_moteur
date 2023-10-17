#pragma once
#include "Vector.h"
class Force{
public:
	Vector direction = Vector(0, 0, 0);

	// Durée de l'application de la force en s
	float timeRemaining;

	Force(Vector direction_, float duration_);
	
	float updateTimeElapsed(float time);

	virtual Vector value();
};

