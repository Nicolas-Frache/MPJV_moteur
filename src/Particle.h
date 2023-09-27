#pragma once
#include "ofMain.h"
#include "Vector.h"
#include "Force.h"
class Particle{
	public :
	Vector position = Vector(0, 0, 0);
	//rotation non utile car particule

	Vector velocity = Vector(0, 0, 0);

	float invertedMass;
	ofColor color;
	float size;
	list<Force> _forces = list<Force>();

	float restitution = 1.0f;
	float friction = 1.0f;
	ofSpherePrimitive sphere;

	float duration = -1.0f;

	public :
		Particle(float X, float Y, float Z, float invertedMass, ofColor color, float size);
		Particle(Vector position, float invertedMass, ofColor color, float size);
		Particle(Vector position, float mass);

		// Gestion de la position
		void setPos(float X, float Y, float Z);
		void setPos(Vector);



		// Gestion de la masse
		void setMass(float mass);
		void setInvMass(float invertedMass);
		void setInfinitMass();

		float getMass();
		float getInvMass();

		// Gestion de l'apparence

		void applyForce(float forceX, float forceY, float forceZ, float duration);
		void integrer(float dt);

		void bounce(Vector normal);

		virtual void update();
		virtual void draw();
};
