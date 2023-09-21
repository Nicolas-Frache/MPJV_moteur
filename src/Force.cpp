#include "Force.h"
#include <algorithm>

Force::Force(Vector direction_, float duration_){
	direction = direction_;
	timeRemaining = duration_;
}

float Force::updateTimeElapsed(float time){
	if (timeRemaining - time > 0) {
		timeRemaining -= time;
		return time;
	}
	return timeRemaining;
}
