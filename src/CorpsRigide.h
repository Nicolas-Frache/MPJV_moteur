#pragma once
#include "ofMain.h"
#include "Vector.h"
#include "Particle.h"
#include "Quaternion.h"
#include "Matrice3x3.h"
#include "Matrice4x4.h"
#include "Torque.h"

class CorpsRigide
{
public:
	Particle* centreMasse;
	Vector demiAxes; //distances du centre de masse aux faces du cube

	ofColor color;

	Quaternion rotation = Quaternion(1, 0, 0, 0);
	Vector angularVelocity = Vector(0, 0, 0);
	Matrice3x3 rotationMatrix = Matrice3x3();

	Vector inverseMomentOfInertia = Vector(0,0,0);

	list<Torque*> _torques = list<Torque*>();

	CorpsRigide(Particle* centreMasse, Vector demiAxes, ofColor color);
	CorpsRigide(Particle* centreMasse, float height, float width, float depth, ofColor color);

	void update();

	void draw();

	void bounce(Vector normal); //pour le bounce on utilise la resti et friction de la particule

	void applyForce(Vector force, float duration);
	void applyForce(float forceX, float forceY, float forceZ, float duration);
	void applyForce(Force* force);

	void applyTorque(Vector torque, float duration);
	void applyTorque(float torqueX, float torqueY, float torqueZ, float duration);
	void removeTorque(Torque* torque);

	void integrer(float dt);

	void setRotation(Quaternion quaternion);

	void ofApplyRotation();

	float normalizeAngle(float angle);
};

