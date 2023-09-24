#include "Fireball.h"
#include "Vector.h"
#include "Particle.h"


Fireball::Fireball(float x_, float y_, float z_, float mass_) 
	: Fireball(Vector(x_,y_,z_), mass_) { }


Fireball::Fireball(Vector position_, float mass_) 
	: Particle(position_, mass_, ofColor(255, 0, 0)) { //on génère une boule de feu avec une position et une masse
	setRestitution(1);
	setFriction(1);
}

void Fireball::update() {
	float dt = ofGetLastFrameTime();
	Particle::integrer(3*dt);
	//ici on génère une particule de trail derrière la boule de feu
	Particle* trail = new Particle(getPos(), 0, ofColor(255, 0, 0));
	trails.push_back(*trail);
	trail->setDuration(0.5);

	////on supprime les trails qui ont dépassé leur durée de vie
	//for (Particle trail : trails) {
	//	if (trail.getDuration() < 0) { 
	//		//on retire la première trail de la liste
	//		trails.pop_front();
	//		delete &trail;
	//	}
	//}
};

void Fireball::draw(){
	//on dessine la boule de feu
	ofSetColor(getColor());
	ofDrawCircle(getPos().x(), getPos().y(), getPos().z(), getSize());
	//on dessine les trails
	for (Particle trail : trails) {
		ofSetColor(trail.getColor());
		ofDrawCircle(trail.getPos().x(), trail.getPos().y(), trail.getPos().z(), trail.getSize());
	}
}