#pragma once
#include "Particle.h"
#include "Vector.h"
#include <list>

class Fireball : public Particle {

public:
	Fireball(float x_, float y_, float z_, float mass_);
	Fireball(Vector position_, float mass_);

	void Fireball::update() override;
	void Fireball::draw() override;
	list<Particle*> trails = list<Particle*>();
};



