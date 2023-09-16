#include "Particle.h"

Particle::Particle(float X, float Y, float Z, float invertedMass, ofColor color) {
	_position = Vector(X, Y, Z);
	_invertedMass = invertedMass;
	_color = color;
}

Particle::Particle(Vector position, float invertedMass, ofColor color) {
	_position = position;
	_invertedMass = invertedMass;
	_color = color;
}

void Particle::setPos(float X, float Y, float Z) {
	_position.set(X, Y, Z);
}

void Particle::setPos(Vector position) {
	_position = position;
}

void Particle::setMass(float invertedMass) {
	_invertedMass = invertedMass;
}

void Particle::setColor(ofColor color) {
	_color = color;
}

void Particle::setForce(Vector force) {
	_force = force;
}

Vector Particle::getPos() {
	return _position;
}

float Particle::getInvMass() {
	return _invertedMass;
}

ofColor Particle::getColor() {
	return _color;
}	

Vector Particle::getVelocity() {
	return _velocity;
}

Vector Particle::getForce() {
	return _force;
}

void Particle::update() {
	_velocity += _force * _invertedMass;
	_position += _velocity;
}

void Particle::draw() {
	ofSetColor(_color);
	ofDrawCircle(_position.x(), _position.y(), _position.z(), 1);
}

void Particle::applyForce(float forceX, float forceY, float forceZ) {
	_force += Vector(forceX, forceY, forceZ);
}

void Particle::integrer(float dt) {
	_velocity += _force * _invertedMass * dt;
	_position += _velocity * dt;
	_force = Vector(0, 0, 0);
}


