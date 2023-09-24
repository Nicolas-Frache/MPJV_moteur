#pragma once
#include "ofMain.h"
#include "Vector.h"
#include "Force.h"
class Particle{
	private :
	Vector _position = Vector(0, 0, 0);
	//rotation non utile car particule

	Vector _velocity = Vector(0, 0, 0);

	float _invertedMass;
	ofColor _color;
	float _size;
	list<Force> _forces = list<Force>();

	float restitution = 1.0f;
	float friction = 1.0f;
	ofSpherePrimitive sphere;

	float duration = -1.0f;

	public :
		Particle(float X, float Y, float Z, float invertedMass, ofColor color, float size);
		Particle(Vector position, float invertedMass, ofColor color, float size);

		// Gestion de la position
		void setPos(float X, float Y, float Z);
		void setPos(Vector);

		void setRestitution(float restitution);
		void setFriction(float friction);

		Vector getPos();

		// Gestion de la masse
		void setMass(float mass);
		void setInvMass(float invertedMass);
		void setInfinitMass();

		float getMass();
		float getInvMass();

		// Gestion de l'apparence

		void setColor(ofColor color);
		void setSize(float size);

		ofColor getColor();
		float getSize();

		virtual void draw();

		void setVelocity(Vector velocity);
		void setVelocity(float X, float Y, float Z);
		Vector getVelocity();

		void applyForce(float forceX, float forceY, float forceZ, float duration);
		void integrer(float dt);

		void bounce(Vector normal);

		void setDuration(float duration);
		float getDuration();

		virtual void update();

};

