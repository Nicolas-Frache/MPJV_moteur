#include "Particle.h"
#include <limits>

Particle::Particle(float X, float Y, float Z, float invertedMass, ofColor color):
	Particle::Particle(Vector(X, Y, Z), invertedMass, color) {
}

Particle::Particle(Vector position, float invertedMass, ofColor color) {
	_position = position;
	_invertedMass = invertedMass;
	_color = color;

	applyForce(0, 9.8, 0, numeric_limits<float>::max());
}

// Gestion de la position

void Particle::setPos(float X, float Y, float Z) {
	_position.set(X, Y, Z);
}

void Particle::setPos(Vector position) {
	_position = position;
}

Vector Particle::getPos() {
	return _position;
}

// Gestion de la masse

void Particle::setMass(float mass) {
	if (mass == 0) {
		Particle::setInfinitMass();
		return;
	}
	_invertedMass = 1 / mass;
}

void Particle::setInvMass(float invertedMass) {
	_invertedMass = invertedMass;
}

void Particle::setInfinitMass() {
	_invertedMass = 0;
}

float Particle::getMass() {
	if (_invertedMass == 0) {
		return 0;
	}
	return 1 / _invertedMass;
}

float Particle::getInvMass() {
	return _invertedMass;
}

// Gestion de l'apparence

void Particle::setColor(ofColor color) {
	_color = color;
}

void Particle::setSize(float size) {
	_size = size;
}

ofColor Particle::getColor() {
	return _color;
}

float Particle::getSize() {
	return _size;
}

void Particle::draw() {
	ofSetColor(_color);
	ofDrawCircle(_position.x(), _position.y(), _position.z(), _size);
}


void Particle::setVelocity(Vector velocity) {
	_velocity = velocity;
}    
    
void Particle::update() {
	float dt = ofGetLastFrameTime();
	integrer(dt);
	cout << "position: " << _position << ", velocity: " << _velocity << endl;
}

Vector Particle::getVelocity() {
	return _velocity;
}

void Particle::applyForce(float forceX, float forceY, float forceZ, float duration) {
	_forces.push_back(Force(Vector(forceX, forceY, forceZ), duration));
}

void Particle::integrer(float dt) {
	// On it�re sur les forces actives
	auto it = _forces.begin();
	while (it != _forces.end()) {
		Force& force = *it;
		float applicationTime = force.updateTimeElapsed(dt);

		_velocity += force.direction * _invertedMass * applicationTime;

		if (applicationTime != dt) {
			it = _forces.erase(it); // Suppression de la force si sa dur�e est termin�e
		}
		else {
			++it; // Element suivant
		}
	}

	// On met � jour la position
	_position += (_velocity * dt);
}






