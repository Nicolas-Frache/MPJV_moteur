#include "Fireball.h"
#include "Vector.h"
#include "Particle.h"

Fireball::Fireball(float x_, float y_, float z_, float mass_, float duration_) 
	: Fireball(Vector(x_,y_,z_), mass_, duration_) { }


Fireball::Fireball(Vector position_, float mass_, float duration_) 
	: Particle(position_, mass_, ofColor_<unsigned char>::red, 17) { //on génère une boule de feu avec une position et une masse
	duration = duration_;
	setRestitution(1);
	setFriction(1);
}


void update() {

}

void draw() {

}