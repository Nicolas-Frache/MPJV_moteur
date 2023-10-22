#pragma once
#include "ofMain.h"
#include "Vector.h"

class Force; //déclaration anticipée de Force

class Particle{
public :
	Vector position = Vector(0, 0, 0);
	Vector velocity = Vector(0, 0, 0);

	float invertedMass;
	ofColor color;
	float size;

	float restitution = 1.0f;
	float friction = 1.0f;
	ofSpherePrimitive sphere;

	float duration = -1.0f;

	public :
		// Constructeurs
		//Particle(float X, float Y, float Z, float invertedMass, ofColor color, float size);
		Particle(Vector position, float invertedMass, ofColor color, float size);

		
		void integrer(float dt);
		void bounce(Vector normal);

		virtual void update();
		virtual void draw();

		
		
		
		// -------------------------------------------
		// -------- Méthodes sans logique  -----------
		// -------------------------------------------

		// Gestion forces ------------------
		Vector forceAccum = Vector(0, 0, 0);		

		void clearAccumulator() {
			forceAccum = Vector(0, 0, 0);
		}

		void addForce(Vector force) {
			forceAccum += force;
		}


		// --------------------------------


		Vector getVelocity() const { 
			return velocity; 
		}

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

		Vector Particle::getPosition() const {
			return position;
		}

		// Gestion de la position
		void Particle::setPos(float X, float Y, float Z) {
			position.set(X, Y, Z);
		}

		// M�thode pour d�finir la position de la particule en utilisant un objet Vector
		void Particle::setPos(Vector position) {
			position = position;
		}

};
