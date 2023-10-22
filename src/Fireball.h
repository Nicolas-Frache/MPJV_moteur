#pragma once
#include "Particle.h"
#include "Vector.h"
#include <list>

class Fireball : public Particle{

	public:
		Fireball(Vector position_, float mass_);

		void Fireball::update() override;
		void Fireball::draw() override;
		list<Particle*> trails = list<Particle*>();
};



