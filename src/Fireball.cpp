#include "Fireball.h"
#include "Vector.h"
#include "Particle.h"


Fireball::Fireball(float x_, float y_, float z_, float mass_) 
	: Fireball(Vector(x_,y_,z_), mass_) { }

Fireball::Fireball(Vector position_, float mass_) 
	: Particle(position_, mass_, ofColor_<unsigned char>::red, 17) { //on g�n�re une boule de feu avec une position et une masse
	setRestitution(1);
	setFriction(1);
}

void Fireball::update() {
	float dt = ofGetLastFrameTime();
	Particle::integrer(3*dt);
	//ici on g�n�re une particule de trail derri�re la boule de feu
	Particle* trail = new Particle(getPos(), 0, ofColor(255, 0, 0), 5);
	trails.push_back(trail);
	trail->setDuration(1.5);

	//on supprime les trails qui ont d�pass� leur dur�e de vie
	auto it = trails.begin();

	while (it != trails.end()) {
		Particle* trail = *it;
		trail->update();

		if (trail->getDuration() < 0) {
			it = trails.erase(it);
		}
		else {
			it++;
		}
	}
};

void Fireball::draw(){
	//on dessine la boule de feu
	Particle::draw();

	//on dessine les trails
	for (Particle* trail : trails) {
		trail->draw();
	}
}