#include "Fireball.h"
#include "Vector.h"
#include "Particle.h"


Fireball::Fireball(float x_, float y_, float z_, float mass_) 
	: Fireball(Vector(x_,y_,z_), mass_) { }

Fireball::Fireball(Vector position_, float mass_) 
	: Particle(position_, mass_, ofColor_<unsigned char>::red, 1.7) { //on g�n�re une boule de feu avec une position et une masse
	
	restitution = 1;
	friction = 1;
}

void Fireball::update() {
	float dt = ofGetLastFrameTime();
	Particle::integrer(dt);
	
	//on genere une particule de trail derriere la boule de feu
	Particle* trail = new Particle(position, 1, ofColor(255, ofRandom(100.f, 200.f), 0), ofRandom(.3f, 1.f));
	trail->duration = ofRandom(1.f, 4.f);

	Vector hor_vel = velocity * 0.7;
	float mult = 2.f;
	float t_x = ofRandom(-1.f, 1.f) * mult + hor_vel.x();
	float t_y = ofRandom(-1.f, 1.f) * mult + hor_vel.y();
	float t_z = ofRandom(-1.f, 1.f) * mult + hor_vel.z();

	trail->velocity = Vector(t_x, t_y, t_z);
	trail->applyForce(new Force(trail, Vector(0, 15, 0), 40.f));
	trails.push_back(trail);	

	//on supprime les trails qui ont d�pass� leur duree de vie
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