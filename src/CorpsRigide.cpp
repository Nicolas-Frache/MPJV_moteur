#include "CorpsRigide.h"
#include "Vector.h"
#include "Particle.h"
#include "ofMain.h"
#include "Force.h"

CorpsRigide::CorpsRigide(Particle* centreMasse, Vector demiAxes, ofColor color) {
	this->centreMasse = centreMasse;
	this->demiAxes = demiAxes;
	this->color = color;

	float m = centreMasse->getMass();
	inverseMomentOfInertia = Vector(
		1 / (1 / 12.0f * m * (2 * demiAxes.y()) * (2 * demiAxes.y()) + (2 * demiAxes.z()) * (2 * demiAxes.z())),
		1 / (1 / 12.0f * m * (2 * demiAxes.x()) * (2 * demiAxes.x()) + (2 * demiAxes.z()) * (2 * demiAxes.z())),
		1 / (1 / 12.0f * m * (2 * demiAxes.x()) * (2 * demiAxes.x()) + (2 * demiAxes.y()) * (2 * demiAxes.y()))
	);
}

CorpsRigide::CorpsRigide(Particle* centreMasse, float height, float width, float depth, ofColor color) {
	this->centreMasse = centreMasse;
	this->demiAxes = Vector(height / 2, width / 2, depth / 2);
	this->color = color;

	float m = centreMasse->getInvMass();
	inverseMomentOfInertia = Vector(
		1 / (1 / 12.0f * m * (2 * demiAxes.y()) * (2 * demiAxes.y()) + (2 * demiAxes.z()) * (2 * demiAxes.z())),
		1 / (1 / 12.0f * m * (2 * demiAxes.x()) * (2 * demiAxes.x()) + (2 * demiAxes.z()) * (2 * demiAxes.z())),
		1 / (1 / 12.0f * m * (2 * demiAxes.x()) * (2 * demiAxes.x()) + (2 * demiAxes.y()) * (2 * demiAxes.y()))
	);
}

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
	ForceRotationnelle* torqueForce = new ForceRotationnelle(this, torque, duration);
	_torques.push_back(torqueForce);
}

void CorpsRigide::applyTorque(float torqueX, float torqueY, float torqueZ, float duration) {
	applyTorque(Vector(torqueX, torqueY, torqueZ), duration);
}

void CorpsRigide::removeTorque(ForceRotationnelle* torque) {
	_torques.remove(torque);
}

void CorpsRigide::bounce(Vector normal) {
	//on peut ajuster ici
	centreMasse->bounce(normal);
}

void CorpsRigide::update() {
	float dt = ofGetLastFrameTime();

	integrer(dt);
	//on affiche la matrice de rotation :
	rotationMatrix.afficher();

	Vector rotationChange = angularVelocity * dt;
	//on affiche rotationchange
	cout << "rotation change: " << rotationChange << endl;
	Matrice4x4 rotationMatrixChange;
	rotationMatrixChange.rotateDeg(rotationChange.x(), 1, 0, 0);
	rotationMatrixChange.rotateDeg(rotationChange.y(), 0, 1, 0);
	rotationMatrixChange.rotateDeg(rotationChange.z(), 0, 0, 1);

	rotationMatrix = rotationMatrixChange.produit(rotationMatrix);

	centreMasse->update();
}

void CorpsRigide::draw() {
	ofPushMatrix();
	applyRotation();
	ofSetColor(color);
	ofDrawBox(centreMasse->position.x(), centreMasse->position.y(), centreMasse->position.z(), demiAxes.x(), demiAxes.y(), demiAxes.z());
	ofPopMatrix();
}

void CorpsRigide::integrer(float dt) {
	centreMasse->integrer(dt);

	auto it = _torques.begin();
	while (it != _torques.end()) {
		float applicationTime = (*it)->updateTimeElapsed(dt);

		cout << "torque: " << (*it)->torque << endl;
		cout << "inverse moment of inertia: " << inverseMomentOfInertia << endl;
		angularVelocity += (*it)->torque.mult_by_component(inverseMomentOfInertia) * applicationTime;
		cout << "angular velocity: " << angularVelocity << endl;
		
		if (applicationTime != dt) {
			it = _torques.erase(it);
		}
		else {
			it++;
		}
	}
}

void CorpsRigide::setRotationMatrix(Matrice4x4 matrix) {
	this->rotationMatrix = matrix;
}

//void CorpsRigide::setRotationMatrix(Quaternion quaternion) {
//	this->rotationMatrix = quaternion.toMatrix();
//}

void CorpsRigide::applyRotation() {
	Vector pos = centreMasse->position;
	Vector rotation = rotationMatrix.getEuler();
	ofTranslate(pos.x(), pos.y(), pos.z());
	ofRotateXDeg(rotation.x());
	ofRotateYDeg(rotation.y());
	ofRotateZDeg(rotation.z());
	ofTranslate(-pos.x(), -pos.y(), -pos.z());
}