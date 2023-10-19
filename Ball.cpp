#include "Ball.h"
#include "../MPJV_moteur/src/Particle.h"

Ball::Ball(float X, float Y, float Z, float invertedMass, ofColor color)
	: Particle(X, Y, Z, invertedMass, color) {

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

void Ball::setRotationZ(float rotationZ) {
	_rotationZ = rotationZ;
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

float Ball::getRotationZ() {
	return _rotationZ;
}

void Ball::update() {
	_velocity += _force * _invertedMass; // voir comment faire pour dt dans le update de ofApp
	//_force = Vector(0, 0, 0); //ça permettrait de pouvoir utiliser integrer(dt)
	cout << "_position: " << _position << " velocity : " << _velocity << ", force : " << _force << endl;
	_position += _velocity;
	_rotationZ += _force.z() * 0.1;
	cout << "_position: " << _position << " velocity : " << _velocity << ", force : " << _force << endl;

	cout << "Adresse de monObjet Balle : " << this << std::endl;
}

void Ball::draw() {
	ofSetColor(getColor());
	ofPushMatrix();
	ofTranslate(_position.x(), _position.y(), _position.z());
	ofRotateZ(_rotationZ * RAD_TO_DEG);

	// Dessiner la Ball
	ofDrawCircle(0, 0, 0, _size);

	// Dessiner un petit cercle coloré au centre du Cannonball
	ofSetColor(ofColor::green); // Couleur du point
	ofDrawCircle(15, 0, 0, 2); // Position relative du point par rapport au Cannonball (0,0,0)

	ofPopMatrix();
}

void Ball::applyForce(float forceX, float forceY, float forceZ) {
	_force += Vector(forceX, forceY, forceZ);
}

void Ball::integrer(float dt) {
	_velocity += _force * _invertedMass * dt;
	_position += _velocity * dt;
	_force = Vector(0, 0, 0);
}


