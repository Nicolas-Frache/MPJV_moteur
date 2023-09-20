#pragma once
#include "ofMain.h"
#include "../MPJV_moteur/src/Particle.h"
#include "../MPJV_moteur/src/Vector.h"


class Ball : public Particle {

private:

	Vector _position = Vector(0, 0, 0);
	//TODO rotation de la ball

	Vector _velocity = Vector(0, 0, 0);
	Vector _force = Vector(0, 0, 0);

	float _invertedMass = 1.0f;
	ofColor _color = ofColor(255, 255, 0);
	float _size = 2.0f;

public:
	Ball(float X, float Y, float Z, float invertedMass, ofColor color);
	Ball(Vector position, float invertedMass, ofColor color);

	void setPos(float X, float Y, float Z);
	void setPos(Vector);
	void setMass(float invertedMass);
	void setColor(ofColor color);
	void setSize(float size);
	void setForce(Vector force);
	void setVelocity(Vector velocity);

	Vector getPos();
	float getInvMass();
	ofColor getColor();
	float getSize();
	Vector getForce();
	Vector getVelocity();

	void update();
	void draw();

	void applyForce(float forceX, float forceY, float forceZ);
	void integrer(float dt);


	Ball() = default;
};


