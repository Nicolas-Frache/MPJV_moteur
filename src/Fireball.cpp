#include "Fireball.h"
#include "Vector.h"
#include "Particle.h"


Fireball::Fireball(Vector position_, float mass_) 
	: Particle(position_, mass_, ofColor_<unsigned char>::red, 17) { //on génère une boule de feu avec une position et une masse
	
	restitution = 1;
	friction = 1;
}

void Fireball::update() {
	float dt = ofGetLastFrameTime();
	Particle::integrer(dt);
	
	//on genere une particule de trail derriere la boule de feu
	Particle* trail = new Particle(position, 1, ofColor(255, ofRandom(100.f, 200.f), 0), ofRandom(3.f, 10.f));
	trail->duration = ofRandom(1.f, 4.f);

	Vector hor_vel = velocity * 0.7;
	float t_x = ofRandom(0.4f, 1.f) * hor_vel.x();
	float t_z = ofRandom(0.4f, 1.f) * hor_vel.z();

	trail->velocity = Vector(t_x, velocity.y() - ofRandom(10, 25), t_z);
	trails.push_back(trail);	

	//on supprime les trails qui ont dépassé leur duree de vie
	auto it = trails.begin();

	while (it != trails.end()) {
		Particle* trail = *it;
		trail->update();

		if (trail->duration < 0) {
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