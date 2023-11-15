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
	this->centreMasse->applyForce(force, duration);
}

void CorpsRigide::update() {
	float dt = ofGetLastFrameTime();
	integrer(dt);
	centreMasse->update();
}

void CorpsRigide::draw() {
	ofSetColor(color);
	ofDrawBox(centreMasse->position.x(), centreMasse->position.y(), centreMasse->position.z(), demiAxes.x(), demiAxes.y(), demiAxes.z());
}

void CorpsRigide::integrer(float dt) {
	centreMasse->integrer(dt);
}