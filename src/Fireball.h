#pragma once
#include "Particle.h"
#include "Vector.h"

class Fireball : public Particle{
	private :
		float duration = 5;

	public:
		Fireball(float x_, float y_, float z_, float mass_, float duration);
		Fireball(Vector position_, float mass_, float duration);
		void update(float time);
		void draw();
};



