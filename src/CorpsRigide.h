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

	Matrice3x3 inverseMomentOfInertia = Matrice3x3();

	list<Torque*> _torques = list<Torque*>();

	CorpsRigide(Particle* centreMasse, Vector demiAxes, ofColor color);
	CorpsRigide(Particle* centreMasse, float height, float width, float depth, ofColor color);

	void update();

	void draw();

	void bounce(Vector normal); //pour le bounce on utilise la resti et friction de la particule

	void integrer(float dt);

	void setRotation(Quaternion quaternion);

	void ofApplyRotation();

	float normalizeAngle(float angle);


	// ------ FONCTIONS DE FORCES SIMPLES ------

	void CorpsRigide::applyForce(Vector force, float duration) {
		centreMasse->applyForce(force, duration);
	}

	void CorpsRigide::applyForce(float forceX, float forceY, float forceZ, float duration) {
		centreMasse->applyForce(forceX, forceY, forceZ, duration);
	}

	void CorpsRigide::applyForce(Force* force) {
		centreMasse->applyForce(force);
	}

	void CorpsRigide::applyTorque(Vector torque, float duration) {
		Torque* torqueForce = new Torque(this, torque, duration);
		_torques.push_back(torqueForce);
	}

	void CorpsRigide::applyTorque(float torqueX, float torqueY, float torqueZ, float duration) {
		applyTorque(Vector(torqueX, torqueY, torqueZ), duration);
	}

	void CorpsRigide::removeTorque(Torque* torque) {
		_torques.remove(torque);
	}

	void ofApplyVisualRotation();
};

