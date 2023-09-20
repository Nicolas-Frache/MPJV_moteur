#include "Balls.h"

Ball::Ball(float X, float Y, float Z, float invertedMass, ofColor color) :
	Particle::Particle(Vector(X, Y, Z), invertedMass, color) {
}

Ball::Ball(Vector position, float invertedMass, ofColor color) {
	_position = position;
	_invertedMass = invertedMass;
	_color = color;
	_force = Vector(0, 0, 0);
}

void Ball::setPos(float X, float Y, float Z) {
	_position.set(X, Y, Z);
}

void Ball::setPos(Vector position) {
	_position = position;
}

void Ball::setMass(float invertedMass) {
	_invertedMass = invertedMass;
}

void Ball::setColor(ofColor color) {
	_color = color;
}

void Ball::setSize(float size) {
	_size = size;
}

void Ball::setVelocity(Vector velocity) {
	_velocity = velocity;
}

void Ball::setForce(Vector force) {
	_force = force;
}

Vector Ball::getPos() {
	return _position;
}

float Ball::getInvMass() {
	return _invertedMass;
}

ofColor Ball::getColor() {
	return _color;
}

float Ball::getSize() {
	return _size;
}

Vector Ball::getVelocity() {
	return _velocity;
}

Vector Ball::getForce() {
	return _force;
}

void Ball::update() {
	_velocity += _force * _invertedMass; // voir comment faire pour dt dans le update de ofApp
	//_force = Vector(0, 0, 0); //ça permettrait de pouvoir utiliser integrer(dt)
	cout << "_position: " << _position << " velocity : " << _velocity << ", force : " << _force << endl;
	_position += _velocity;
	cout << "_position: " << _position << " velocity : " << _velocity << ", force : " << _force << endl;
	cout << "Adresse de monObjet : " << this << std::endl;
}

void Ball::draw() {
	ofSetColor(_color);
	ofDrawCircle(_position.x(), _position.y(), _position.z(), _size);
}

void Ball::applyForce(float forceX, float forceY, float forceZ) {
	_force += Vector(forceX, forceY, forceZ);
}

void Ball::integrer(float dt) {
	_velocity += _force * _invertedMass * dt;
	_position += _velocity * dt;
	_force = Vector(0, 0, 0);
}