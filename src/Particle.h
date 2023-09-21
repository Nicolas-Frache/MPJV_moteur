#pragma once
#include "ofMain.h"
#include "Vector.h"
#include "Force.h"
class Particle{
	private :
	Vector _position = Vector(0, 0, 0);
	//rotation non utile car particule

	Vector _velocity = Vector(0, 0, 0);

	float _invertedMass = 1.0f; 
	ofColor _color = ofColor(255, 255, 255); //ça parait être une bonne idée de pouvoir choisir la couleur pour faire des tests plus tard
	float _size = 1.0f;
	list<Force> _forces = list<Force>();

	public :
		Particle(float X, float Y, float Z, float invertedMass, ofColor color);
		Particle(Vector position, float invertedMass, ofColor color);

		// Gestion de la position
		void setPos(float X, float Y, float Z);
		void setPos(Vector);

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

		void draw();

		void setVelocity(Vector velocity);
		void setVelocity(float X, float Y, float Z);
		Vector getVelocity();

		void applyForce(float forceX, float forceY, float forceZ, float duration);
		void integrer(float dt);

		void update();

};

