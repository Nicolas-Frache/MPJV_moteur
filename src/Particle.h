#pragma once
#include "ofMain.h"
#include "Vector.h"
class Particle
{
	private :
	Vector _position = Vector(0, 0, 0);
	//rotation non utile car particule

	Vector _velocity = Vector(0, 0, 0);
	Vector _force = Vector(0, 0, 0);

	float _invertedMass = 1.0f; 
	ofColor _color = ofColor(255, 255, 255); //ça parait être une bonne idée de pouvoir choisir la couleur pour faire des tests plus tard

	public :
		Particle(float X, float Y, float Z, float invertedMass, ofColor color);
		Particle(Vector position, float invertedMass, ofColor color);

		void setPos(float X, float Y, float Z);
		void setPos(Vector);
		void setMass(float invertedMass);
		void setColor(ofColor color);
		void setForce(Vector force);

		Vector getPos();
		float getInvMass();
		ofColor getColor();
		Vector getVelocity();
		Vector getForce();

		void update();
		void draw();

		void applyForce(float forceX, float forceY, float forceZ);
		void integrer(float dt);

};

