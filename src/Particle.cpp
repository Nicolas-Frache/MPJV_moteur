#include "Particle.h"

Particle::Particle(float X, float Y, float Z, float invertedMass, ofColor color):
	Particle::Particle(Vector(X, Y, Z), invertedMass, color) {
}

Particle::Particle(Vector position, float invertedMass, ofColor color) {
	_position = position;
	_invertedMass = invertedMass;
	_color = color;
	_force = Vector(0, 0, 0);
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


// Gestion de la physique

void Particle::setForce(Vector force) {
	_force = force;
}

Vector Particle::getForce() {
	return _force;
}

void Particle::setVelocity(Vector velocity) {
	_velocity = velocity;
}

Vector Particle::getVelocity() {
	return _velocity;
}


void Particle::applyForce(float forceX, float forceY, float forceZ) {
	_force += Vector(forceX, forceY, forceZ);
}

void Particle::integrer(float dt) {
	_velocity += _force * _invertedMass * dt;
	_position += (_velocity * dt);
	_force = Vector(0, 0, 0);
}


void Particle::update() {
	applyForce(0, 9.8/30, 0);
	integrer(1.0 / 30);
}






