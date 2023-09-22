#pragma once
#include "../MPJV_moteur/src/Particle.h"
#include "../MPJV_moteur/src/Vector.h"

class Laser : public Particle
{

private:

	Vector _startPoint = Vector(0, 0, 0);
	Vector _endPoint = Vector(0, 0, 0);
	
	Vector _velocity = Vector(0, 0, 0);
	Vector _force = Vector(0, 0, 0);
	Vector _rotation = Vector(0, 0, 0);

	float _invertedMass = 1.0f;
	ofColor _color = ofColor(255, 255, 255);
	float _size = 1.0f;

public:

	Laser(float X1, float Y1, float Z1, float X2, float Y2, float Z2, float invertedMass, ofColor color);

	void setStartPoint(Vector startPoint);
	void setEndPoint(Vector endPoint);
	void setPos(Vector, Vector);
	void setMass(float invertedMass);
	void setColor(ofColor color);
	void setSize(float size);
	void setForce(Vector force);
	void setVelocity(Vector velocity);

	Vector getStartPointPos();
	Vector getEndPointPos();
	float getInvMass();
	ofColor getColor();
	float getSize();
	Vector getForce();
	Vector getVelocity();

	void update();
	void draw();

	void applyForce(float forceX, float forceY, float forceZ);
	void integrer(float dt);

};

