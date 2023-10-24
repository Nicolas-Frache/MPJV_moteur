#pragma once
#include "ofMain.h"
#include "Vector.h"
#include "Force.h"

class Force; //déclaration anticipée de Force

class Particle{
	public :
	Vector position = Vector(0, 0, 0);
	//rotation non utile car particule

	Vector velocity = Vector(0, 0, 0);

	float invertedMass;
	ofColor color;
	float size;
	list<Force*> _forces = list<Force*>();

	float restitution = 1.0f;
	float friction = 1.0f;
	ofSpherePrimitive sphere;

	float duration = -1.0f;

	public :
		Particle(float X, float Y, float Z, float invertedMass, ofColor color, float size);
		Particle(Vector position, float invertedMass, ofColor color, float size);

		// Gestion de l'apparence

		void applyForce(float forceX, float forceY, float forceZ, float duration);
		void applyForce(Vector force, float duration);
		void applyForce(Force* force);

		
		void integrer(float dt);

		void bounce(Vector normal);

		virtual void update();
		virtual void draw();


		// POSITION
		void Particle::setPos(float X, float Y, float Z) {
			position.set(X, Y, Z);
		}
		void Particle::setPos(Vector position) {
			position = position;
		}
		Vector Particle::getPosition() const {
			return position;
		}

		// VELOCITY
		void Particle::setVelocity(float X, float Y, float Z) {
			velocity.set(X, Y, Z);
		}
		// getter
		Vector Particle::getVelocity() {
			return velocity;
		}



		// MASSE
		void Particle::setMass(float mass) {
			if (mass == 0) {
				Particle::setInfinitMass();
				return;
			}
			invertedMass = 1 / mass;
		}
		void Particle::setInvMass(float invertedMass) {
			invertedMass = invertedMass;
		}
		void Particle::setInfinitMass() {
			invertedMass = 0;
		}
		float Particle::getMass() {
			if (invertedMass == 0) {
				return 0;
			}
			return 1 / invertedMass;
		}
		float Particle::getInvMass() {
			return invertedMass;
		}



};
