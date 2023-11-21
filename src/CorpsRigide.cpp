#include "CorpsRigide.h"
#include "Vector.h"
#include "Particle.h"
#include "ofMain.h"
#include "Force.h"

CorpsRigide::CorpsRigide(Particle* centreMasse, Vector demiAxes, ofColor color) {
	this->centreMasse = centreMasse;
	this->demiAxes = demiAxes;
	this->color = color;
}

CorpsRigide::CorpsRigide(Particle* centreMasse, float height, float width, float depth, ofColor color) {
	this->centreMasse = centreMasse;
	this->demiAxes = Vector(height / 2, width / 2, depth / 2);
	this->color = color;
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

void CorpsRigide::bounce(Vector normal) {
	//on peut ajuster ici
	centreMasse->bounce(normal);
}

void CorpsRigide::update() {
	float dt = ofGetLastFrameTime();
	integrer(dt);
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